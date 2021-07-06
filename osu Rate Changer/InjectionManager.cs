using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Timers;
using System.Reactive.Linq;
using static osu_Rate_Changer.Util;
using System.Reactive.Concurrency;
using System.Threading;

namespace osu_Rate_Changer
{
	public class InjectionManager
	{
        private System.Timers.Timer timer;

		public IntPtr Handle { get; private set; }

        private IpcHandler IpcInstance { get; set; }

        public delegate void HandleClosedCallback();
		private event HandleClosedCallback ClosedCallback;

		public delegate void HandleSetSpeed(double state);
		public event HandleSetSpeed SetSpeed;

		public delegate void HandleToggleBpmScale(bool state);
		public event HandleToggleBpmScale ToggleBpmScale;

		// protobuf serialisation error when DoubleVal is set to 0. probably a bug
        private double _speed = 1.0f;
		public double Speed
		{
			get => _speed;
			set
			{
                IpcInstance.Send(new Messaging.Msg {
                    UiMsg = Messaging.UiMsg.Setspeed,
                    DoubleVal = value
                });
            }
		}

        private bool _bpmScaleFix;
        public bool BpmScaleFix
        {
            get => _bpmScaleFix;
            set
			{
				IpcInstance.Send(new Messaging.Msg {
					UiMsg = Messaging.UiMsg.Setbpmscale,
					BoolVal = value
				});
			}
        }


        private InjectionManager(IntPtr handle, IpcHandler ipcHandler, HandleClosedCallback handleClosedCallback)
		{
			Handle = handle;
            IpcInstance = ipcHandler;

			ClosedCallback = handleClosedCallback;

            timer = new System.Timers.Timer(1000);
            timer.Elapsed += new ElapsedEventHandler(ValidateHandleEvent);
            timer.Start();

            ipcHandler.ResponseMessage += IpcHandler_ResponseMessage;
		}

        private void IpcHandler_ResponseMessage(Messaging.Msg msg)
        {
            switch (msg.UiMsg)
            {
                case Messaging.UiMsg.Setspeed:
					_speed = msg.DoubleVal;
					SetSpeed?.Invoke(Speed);
                    break;
                case Messaging.UiMsg.Setbpmscale:
					_bpmScaleFix = msg.BoolVal;
					ToggleBpmScale?.Invoke(BpmScaleFix);
                    break;
                default:
                    break;
            }
        }

		private void ValidateHandleEvent(object sender, ElapsedEventArgs e)
		{
			if (HasHandleExited(Handle))
			{
				Task.Run(() => MessageBox.Show("Game handle was closed"));
				ClosedCallback.Invoke();
			}
		}

		// wtf are you supposed to do if this fails lol
        private static bool HasHandleExited(IntPtr handle) => GetExitCodeProcess(handle, out uint exitcode) && exitcode != 259;

        public static InjectionManager HookInstance(uint pid, string dllName, IpcHandler ipcHandler, HandleClosedCallback handleClosedCallback, Action<State.Status, string> stateHandler)
		{
			IntPtr handle = OpenProcess(ProcessAccessFlags.VirtualMemoryOperation | ProcessAccessFlags.VirtualMemoryWrite | ProcessAccessFlags.VirtualMemoryRead, false, pid);

			if (handle == IntPtr.Zero)
			{
				stateHandler?.Invoke(State.Status.NOTFOUND, "Failed to obtain handle");
				return null;
			}

			//if (!Util.CreateSlot())
			//{
			//	stateHandler?.Invoke(State.Status.FAILED, "Failed to create mailslot");
			//	return null;
			//}

			if (!Util.Inject(pid, Path.GetFullPath(dllName)))
			{
				stateHandler?.Invoke(State.Status.FAILED, "Injection failed");
				return null;
			}

			//IntPtr freezeAddr = (IntPtr)Util.ReadSlot();

			// block thread until remote process has signaled or takes too long
			var isReady = Observable.Merge(
					Observable.Timer(TimeSpan.FromSeconds(5))
						.Select(_ => false)
						.Materialize(),
					ipcHandler.IsReadyToSend.Materialize()
				)
				.TakeWhile(n => n.HasValue)
				.Dematerialize()
				.Wait();

			if (!isReady)
            {
				stateHandler?.Invoke(State.Status.FAILED, "Injection failed");
				return null;
            }

			stateHandler?.Invoke(State.Status.SUCEESS, null);
			return new InjectionManager(handle, ipcHandler, handleClosedCallback);
		}

		public void UnregisterEvents()
		{
			timer?.Dispose();
			ClosedCallback = null;
		}

		~InjectionManager()
		{
			UnregisterEvents();
		}
	}
}
