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
	class Util
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


		[DllImport("kernel32.dll")]
		public static extern IntPtr OpenProcess(ProcessAccessFlags processAccess, bool bInheritHandle, uint processId);

		static IntPtr handle;

		public static void GetHandle()
		{
			handle = OpenProcess(ProcessAccessFlags.VirtualMemoryOperation | ProcessAccessFlags.VirtualMemoryWrite | ProcessAccessFlags.VirtualMemoryRead, false, MainForm.procPid);

			if (handle == IntPtr.Zero)
			{
				Console.WriteLine("Failed to obtain handle");
			}
		}

		public static void SetSpeed(double speedMul)
		{
			Console.WriteLine("Handle: {0:X}\n", (uint)handle);

			WriteProcessMemory(handle, (IntPtr)MainForm.freezeAddr, 1147.0f * speedMul, sizeof(double), out IntPtr a);
		}

		public static int Map(int v, int omin, int omax, int nmin, int nmax)
		{
			if (omin == omax)
				return (int)((float)(nmax - nmin) / 2);
			return (int)((float)(v - omin) / (omax - omin) * (nmax - nmin) + nmin);
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
