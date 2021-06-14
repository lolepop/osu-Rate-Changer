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
		static readonly string procName = "osu!.exe";
		static readonly string dllName = "virus.dll";
		static readonly string saveFile = "osuratechanger.xml";

		public InjectionManager InternalManager { get; set; }

		public static Size defaultBtnSize = new Size(65, 30);

		private State.Status _injectedStatus;
		public State.Status InjectedStatus
		{
			get => _injectedStatus;
			set
			{
				_injectedStatus = value;

				Enabled = true;
				UpdateSpeedBtn.Enabled = false;
				InjectBtn.Enabled = true;

				switch (value)
				{
					case State.Status.SUCEESS:
						StatusLabel.BackColor = Status.SUCCESS;
						StatusLabel.Text = "Injected";
						InjectBtn.Text = "Injected";
						InjectBtn.Enabled = false;
						forceNormalBox.Enabled = true;
						UpdateSpeedBtn.Enabled = true;
						break;
					case State.Status.FAILED:
						StatusLabel.BackColor = Status.FAILED;
						StatusLabel.Text = "Injection failed";
						break;
					case State.Status.NOTFOUND:
						StatusLabel.BackColor = Status.FAILED;
						InjectBtn.Text = "Inject";
						StatusLabel.Text = "No process open";
						break;
					case State.Status.READY:
						StatusLabel.BackColor = Status.SUCCESS;
						InjectBtn.Text = "Inject";
						StatusLabel.Text = "Ready to inject";
						break;
					case State.Status.PROCESSING:
						Enabled = false;
						StatusLabel.BackColor = Status.PROCESSING;
						StatusLabel.Text = "Injecting...";
						break;
					default:
						break;
				}
			}
		}

		private void MainForm_Load(object sender, EventArgs e)
		{
			#if DEBUG
				Util.AllocConsole();
			#endif

			bool isOpen = Util.GetProcessId(procName) != 0;
			InjectedStatus = isOpen ? State.Status.READY : State.Status.NOTFOUND;

			EditGroup.Visible = false;

			if (File.Exists(saveFile))
				GenerateButtons(BtnData.Load(saveFile));

		}

		private void HandleClosedCallback()
		{
			InternalManager.UnregisterEvents();
			InternalManager = null;

			InjectedStatus = State.Status.READY;
		}

		private void InjectBtn_Click(object sender, EventArgs e)
		{
			Enabled = false;
			InjectedStatus = State.Status.PROCESSING;

			uint pid = Util.GetProcessId(procName);

			if (pid == 0)
			{
				InjectedStatus = State.Status.NOTFOUND;
				return;
			}

			InternalManager = InjectionManager.HookInstance(pid, dllName, HandleClosedCallback, (State.Status status, string err) => {
				InjectedStatus = status;
				
				Console.WriteLine($"Injection: {nameof(status)}, return: {err}");
				if (status != State.Status.SUCEESS && status != State.Status.PROCESSING)
					MessageBox.Show($"Failed to hook the game: {err}");
			});

		}

		private void RateTrackBar_Scroll(object sender, EventArgs e)
		{
			RateUpDown.Value = RateTrackBar.Value / 1000.0m;
		}

		private void RateUpDown_ValueChanged(object sender, EventArgs e)
		{
			RateTrackBar.Value = Util.Clamp((int)(RateUpDown.Value * 1000.0m), RateTrackBar.Minimum, RateTrackBar.Maximum);
		}

		private void UpdateSpeedBtn_Click(object sender, EventArgs e)
		{
			if (!forceNormalBox.Checked)
				InternalManager.Speed = (double)RateUpDown.Value;
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
					c.Click += (object sender, EventArgs e) => InternalManager.Speed = float.Parse(c.Text);
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
					c.Click += (object sender, EventArgs e) => InternalManager.Speed = float.Parse(c.Text);
				}


				c.Size = size;
				c.Location = pos;
				c.Text = lol.ToString();
				c.AutoSize = false;
				controls.Add(c);
			}

			BtnGroup.Controls.Clear();

			foreach (var a in controls)
				BtnGroup.Controls.Add(a);
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

		private void forceNormalBox_CheckedChanged(object sender, EventArgs e)
		{
			InternalManager.Speed = forceNormalBox.Checked ? 0 : (float)RateUpDown.Value;
		}

		public MainForm()
		{
			InitializeComponent();
		}

	}
}
