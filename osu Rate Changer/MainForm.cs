using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

#pragma warning disable IDE1006

namespace osu_Rate_Changer
{
	public partial class MainForm : Form
	{
		static string procName = "osu!.exe";
		static string dllName = "virus.dll";
		static string saveFile = "osuratechanger.xml";

		public static uint procPid;
		public static uint freezeAddr;
		public static float freezeMul = 1.0f;

		public static Size defaultBtnSize = new Size(65, 30);

		public MainForm()
		{
			InitializeComponent();
		}

		private void MainForm_Load(object sender, EventArgs e)
		{
			#if DEBUG
				AllocConsole();
			#endif

			bool isOpen = getProcessId("osu!.exe") != 0;
			StatusLabel.BackColor = isOpen ? Status.SUCCESS : Status.FAILED;
			StatusLabel.Text = isOpen ? "Ready to inject" : "No process open";

			EditGroup.Visible = false;

			if (File.Exists(saveFile))
			{
				GenerateButtons(BtnData.Load(saveFile));
			}


			UpdateSpeedBtn.Enabled = false;
			Enabled = false;
			createSlot();
			Enabled = true;
		}

		private void InjectBtn_Click(object sender, EventArgs e)
		{
			Enabled = false;

			uint pid = getProcessId(procName);

			if (pid == 0)
			{
				StatusLabel.BackColor = Status.FAILED;
				StatusLabel.Text = "No process open";
				Enabled = true;
				return;
			}

			procPid = pid;

			StatusLabel.BackColor = Status.PROCESSING;
			StatusLabel.Text = "Injecting...";

			if (inject(pid, Path.GetFullPath(dllName)))
			{

				StatusLabel.Text = "Waiting for IPC...";
				StatusLabel.BackColor = Status.PROCESSING;

				freezeAddr = readSlot();

				StatusLabel.BackColor = Status.SUCCESS;
				StatusLabel.Text = "Injected";
				InjectBtn.Text = "Injected";

				Enabled = true;
				InjectBtn.Enabled = false;
				UpdateSpeedBtn.Enabled = true;

				Util.GetHandle();
				Util.SetSpeed(freezeMul);

				return;
			}

			Enabled = true;
			StatusLabel.BackColor = Status.FAILED;
			StatusLabel.Text = "Injection failed";

		}

		private void RateTrackBar_Scroll(object sender, EventArgs e)
		{
			RateUpDown.Value = RateTrackBar.Value / 1000.0m;
		}

		private void RateUpDown_ValueChanged(object sender, EventArgs e)
		{
			RateTrackBar.Value = Math.Min(Math.Max((int)(RateUpDown.Value * 1000.0m), RateTrackBar.Minimum), RateTrackBar.Maximum);
		}

		private void UpdateSpeedBtn_Click(object sender, EventArgs e)
		{
			Util.SetSpeed((float)RateUpDown.Value);
		}

		private void RangeLockCheckbox_CheckedChanged(object sender, EventArgs e)
		{
			if (RangeLockCheckbox.Checked)
			{
				RateUpDown.Minimum = 0.5m;
				RateUpDown.Maximum = 2.0m;
			}
			else
			{
				RateUpDown.Minimum = 0;
				RateUpDown.Maximum = int.MaxValue;
			}
		}

		private void GroupBoxPaint(object sender, PaintEventArgs e)
		{
			GroupBox box = (GroupBox)sender;
			e.Graphics.Clear(SystemColors.Control);
			e.Graphics.DrawString(box.Text, box.Font, Brushes.Black, 0, 0);
		}

		static bool editMode;
		private void EditBtn_Click(object sender, EventArgs e)
		{
			editMode = !editMode;
			EditBtn.Text = editMode ? "Done" : "Edit";
			EditGroup.Visible = editMode;

			ConvBtnGroup(editMode);

			if (!editMode)
			{
				ArrangeBtnGroup();
				BtnGroup.Enabled = UpdateSpeedBtn.Enabled;

				BtnData btnData = new BtnData();

				foreach (Control a in BtnGroup.Controls)
				{
					btnData.vals.Add(a.Text);
				}


				File.WriteAllText(saveFile, btnData.Serialise());

			}
			else
			{
				BtnGroup.Enabled = true;
			}

		}

		void GenerateButtons(BtnData data)
		{
			foreach (string val in data.vals)
			{
				if (float.TryParse(val, out float a))
				{
					Button c = new Button();
					c.Size = defaultBtnSize;
					c.Text = a.ToString();
					c.Click += delegate (object sender, EventArgs e) { Util.SetSpeed(float.Parse(c.Text)); };
					BtnGroup.Controls.Add(c);
				}
			}
			ArrangeBtnGroup();
		}

		void ConvBtnGroup(bool val) // false when edit mode is turned off
		{
			List<Control> controls = new List<Control>(); // idk what controlcollection wants to be initialised with

			foreach (Control a in BtnGroup.Controls)
			{
				var size = a.Size;
				var pos = a.Location;
				var text = a.Text;

				if (!float.TryParse(text, out float lol))
					continue;

				Control c;

				if (val)
				{
					c = new TextBox();
					((TextBox)c).TextAlign = HorizontalAlignment.Center;
				}
				else
				{
					c = new Button();
					c.Click += delegate (object sender, EventArgs e) { Util.SetSpeed(float.Parse(c.Text)); };
				}


				c.Size = size;
				c.Location = pos;
				c.Text = lol.ToString();
				c.AutoSize = false;
				controls.Add(c);
			}

			BtnGroup.Controls.Clear();

			foreach (var a in controls)
			{
				BtnGroup.Controls.Add(a);
			}
		}

		void ArrangeBtnGroup()
		{
			List<Control> controls = new List<Control>();
			foreach (Control a in BtnGroup.Controls)
				controls.Add(a);

			if (controls.Count == 0)
				return;

			if (controls[0] is Button)
				controls.Sort((a, b) => float.Parse(a.Text).CompareTo(float.Parse(b.Text)));

			List<Control> c = controls.ToLookup(x => x.Text).Select(x => x.First()).ToList();

			BtnGroup.Controls.Clear();

			foreach (var a in c)
				BtnGroup.Controls.Add(a);


			for (int i = 0; i < BtnGroup.Controls.Count; i++)
				BtnGroup.Controls[i].Location = new Point(Util.Map(i, 0, BtnGroup.Controls.Count - 1, 0, BtnGroup.Size.Width - BtnGroup.Controls[i].Size.Width), (BtnGroup.Size.Height - BtnGroup.Controls[i].Size.Height / 2) / 2);
		}

		private void AddBtn_Click(object sender, EventArgs e)
		{
			TextBox tb = new TextBox();
			tb.TextAlign = HorizontalAlignment.Center;
			tb.AutoSize = false;
			tb.Size = defaultBtnSize;

			BtnGroup.Controls.Add(tb);

			ArrangeBtnGroup();

		}

		private void UpdateSpeedEnabled(object sender, EventArgs e)
		{
			BtnGroup.Enabled = UpdateSpeedBtn.Enabled;
		}

		[DllImport("injector.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern bool inject(uint pid, string dll);

		[DllImport("injector.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern uint getProcessId([MarshalAsAttribute(UnmanagedType.LPWStr)] string procName);

		[DllImport("injector.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern bool createSlot(int attempt = 0);

		[DllImport("injector.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern uint readSlot();

		[DllImport("kernel32.dll")]
		static extern bool AllocConsole();

	}
}
