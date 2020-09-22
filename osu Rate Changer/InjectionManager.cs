using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Timers;
using static osu_Rate_Changer.Util;

namespace osu_Rate_Changer
{
	public class InjectionManager
	{
		private System.Timers.Timer timer;

		public IntPtr Handle { get; private set; }
		public IntPtr FreezeAddr { get; private set; }

		public delegate void HandleClosedCallback();
		private event HandleClosedCallback ClosedCallback;

		private double _speed = 1.0f;
		public double Speed
		{
			get => _speed;
			set
			{
				_speed = value;
				SetSpeed(value);
			}
		}

		private InjectionManager(IntPtr handle, IntPtr freezeAddr, HandleClosedCallback handleClosedCallback)
		{
			Handle = handle;
			FreezeAddr = freezeAddr;
			Speed = _speed; // set default once;

			ClosedCallback = handleClosedCallback;

			timer = new System.Timers.Timer(5000);
			timer.Elapsed += new ElapsedEventHandler(ValidateHandleEvent);
			timer.Start();
		}

		private void ValidateHandleEvent(object sender, ElapsedEventArgs e)
		{
			// wtf are you supposed to do if this fails lol
			if (GetExitCodeProcess(Handle, out uint exitcode) && exitcode != 259)
			{
				Task.Run(() => MessageBox.Show("Game handle was closed"));
				ClosedCallback.Invoke();
			}
		}

		public static InjectionManager HookInstance(uint pid, string dllName, HandleClosedCallback handleClosedCallback, Action<State.Status, string> stateHandler)
		{
			IntPtr handle = OpenProcess(ProcessAccessFlags.VirtualMemoryOperation | ProcessAccessFlags.VirtualMemoryWrite | ProcessAccessFlags.VirtualMemoryRead, false, pid);

			if (handle == IntPtr.Zero)
			{
				stateHandler?.Invoke(State.Status.NOTFOUND, "Failed to obtain handle");
				return null;
			}

			if (!Util.CreateSlot())
			{
				stateHandler?.Invoke(State.Status.FAILED, "Failed to create mailslot");
				return null;
			}

			if (!Util.Inject(pid, Path.GetFullPath(dllName)))
			{
				stateHandler?.Invoke(State.Status.FAILED, "Injection failed");
				return null;
			}

			IntPtr freezeAddr = (IntPtr)Util.ReadSlot();

			stateHandler?.Invoke(State.Status.SUCEESS, null);
			return new InjectionManager(handle, freezeAddr, handleClosedCallback);
		}

		private void SetSpeed(double speedMul)
		{
			Console.WriteLine("Handle: {0:X}\n", (uint)Handle);

			//WriteProcessMemory(handle, (IntPtr)MainForm.freezeAddr, 1147.0f * speedMul, sizeof(double), out IntPtr a);
			WriteProcessMemory(Handle, FreezeAddr, speedMul, sizeof(double), out IntPtr a);
		}

		public void UnregisterEvents()
		{
			timer.Stop();
			ClosedCallback = null;
		}

		~InjectionManager()
		{
			UnregisterEvents();
		}
	}
}
