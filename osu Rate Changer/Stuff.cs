using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace osu_Rate_Changer
{
	public class Util
	{
		[Flags]
		public enum ProcessAccessFlags : uint
		{
			All = 0x001F0FFF,
			Terminate = 0x00000001,
			CreateThread = 0x00000002,
			VirtualMemoryOperation = 0x00000008,
			VirtualMemoryRead = 0x00000010,
			VirtualMemoryWrite = 0x00000020,
			DuplicateHandle = 0x00000040,
			CreateProcess = 0x000000080,
			SetQuota = 0x00000100,
			SetInformation = 0x00000200,
			QueryInformation = 0x00000400,
			QueryLimitedInformation = 0x00001000,
			Synchronize = 0x00100000
		}


		[DllImport("kernel32.dll")]
		public static extern bool WriteProcessMemory(
			IntPtr hProcess,
			IntPtr lpBaseAddress,
			byte[] lpBuffer,
			Int32 nSize,
			out IntPtr lpNumberOfBytesWritten
		);

		[DllImport("kernel32.dll")]
		public static extern bool WriteProcessMemory(
			IntPtr hProcess,
			IntPtr lpBaseAddress,
			[MarshalAs(UnmanagedType.AsAny)] object lpBuffer,
			int dwSize,
			out IntPtr lpNumberOfBytesWritten
		);

		[DllImport("kernel32.dll", SetLastError = true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		public static extern bool GetExitCodeProcess(IntPtr hProcess, out uint lpExitCode);

		[DllImport("kernel32.dll")]
		public static extern IntPtr OpenProcess(ProcessAccessFlags processAccess, bool bInheritHandle, uint processId);

		[DllImport("injector.dll", EntryPoint = "inject", CallingConvention = CallingConvention.Cdecl)]
		public static extern bool Inject(uint pid, string dll);

		[DllImport("injector.dll", EntryPoint = "getProcessId", CallingConvention = CallingConvention.Cdecl)]
		public static extern uint GetProcessId([MarshalAsAttribute(UnmanagedType.LPWStr)] string procName);

		[DllImport("injector.dll", EntryPoint = "createSlot", CallingConvention = CallingConvention.Cdecl)]
		public static extern bool CreateSlot(int attempt = 0);

		[DllImport("injector.dll", EntryPoint = "readSlot", CallingConvention = CallingConvention.Cdecl)]
		public static extern uint ReadSlot();

		[DllImport("kernel32.dll")]
		public static extern bool AllocConsole();

		public static int Map(int v, int omin, int omax, int nmin, int nmax)
		{
			if (omin == omax)
				return (int)((float)(nmax - nmin) / 2);
			return (int)((float)(v - omin) / (omax - omin) * (nmax - nmin) + nmin);
		}

		public static int Clamp(dynamic val, dynamic min, dynamic max)
		{
			return (int)Math.Min(Math.Max(val, min), max);
		}
	}

	[Serializable]
	[XmlRoot(ElementName = "buttons")]
	public class BtnData
	{
		[XmlArrayItem(ElementName = "val")]
		public List<string> vals = new List<string>();

		public string Serialise()
		{
			var s = new XmlSerializer(typeof(BtnData));

			var sw = new StringWriter(new StringBuilder());
			s.Serialize(sw, this);

			return sw.GetStringBuilder().ToString();
		}

		public static BtnData Load(string file)
		{
			using (var reader = File.OpenText(file))
			{
				var s = new XmlSerializer(typeof(BtnData));
				var a = (BtnData)s.Deserialize(reader);

				//foreach (var b in a.vals)
				//	Console.WriteLine(b);

				return a;
			}
		}
	}

	public static class Status
	{
		public static Color SUCCESS = Color.FromArgb(255, 173, 255, 47);
		public static Color PROCESSING = Color.FromArgb(255, 255, 165, 0);
		public static Color FAILED = Color.FromArgb(255, 255, 104, 47);
	}
}
