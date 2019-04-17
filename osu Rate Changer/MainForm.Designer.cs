namespace osu_Rate_Changer
{
	partial class MainForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.InjectBtn = new System.Windows.Forms.Button();
			this.StatusLabel = new System.Windows.Forms.Label();
			this.RateTrackBar = new System.Windows.Forms.TrackBar();
			this.RateUpDown = new System.Windows.Forms.NumericUpDown();
			this.label1 = new System.Windows.Forms.Label();
			this.UpdateSpeedBtn = new System.Windows.Forms.Button();
			this.RangeLockCheckbox = new System.Windows.Forms.CheckBox();
			this.EditBtn = new System.Windows.Forms.Button();
			this.EditGroup = new System.Windows.Forms.GroupBox();
			this.AddBtn = new System.Windows.Forms.Button();
			this.BtnGroup = new System.Windows.Forms.GroupBox();
			this.forceNormalBox = new System.Windows.Forms.CheckBox();
			((System.ComponentModel.ISupportInitialize)(this.RateTrackBar)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.RateUpDown)).BeginInit();
			this.EditGroup.SuspendLayout();
			this.SuspendLayout();
			// 
			// InjectBtn
			// 
			this.InjectBtn.Location = new System.Drawing.Point(580, 267);
			this.InjectBtn.Name = "InjectBtn";
			this.InjectBtn.Size = new System.Drawing.Size(156, 41);
			this.InjectBtn.TabIndex = 0;
			this.InjectBtn.Text = "Inject";
			this.InjectBtn.UseVisualStyleBackColor = true;
			this.InjectBtn.Click += new System.EventHandler(this.InjectBtn_Click);
			// 
			// StatusLabel
			// 
			this.StatusLabel.BackColor = System.Drawing.Color.GreenYellow;
			this.StatusLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.StatusLabel.Location = new System.Drawing.Point(582, 223);
			this.StatusLabel.Name = "StatusLabel";
			this.StatusLabel.Size = new System.Drawing.Size(156, 41);
			this.StatusLabel.TabIndex = 1;
			this.StatusLabel.Text = "Ready to inject";
			this.StatusLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// RateTrackBar
			// 
			this.RateTrackBar.LargeChange = 100;
			this.RateTrackBar.Location = new System.Drawing.Point(12, 98);
			this.RateTrackBar.Maximum = 2000;
			this.RateTrackBar.Minimum = 500;
			this.RateTrackBar.Name = "RateTrackBar";
			this.RateTrackBar.Size = new System.Drawing.Size(776, 45);
			this.RateTrackBar.SmallChange = 10;
			this.RateTrackBar.TabIndex = 2;
			this.RateTrackBar.TickStyle = System.Windows.Forms.TickStyle.None;
			this.RateTrackBar.Value = 1000;
			this.RateTrackBar.Scroll += new System.EventHandler(this.RateTrackBar_Scroll);
			// 
			// RateUpDown
			// 
			this.RateUpDown.DecimalPlaces = 2;
			this.RateUpDown.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
			this.RateUpDown.Location = new System.Drawing.Point(401, 149);
			this.RateUpDown.Maximum = new decimal(new int[] {
            2,
            0,
            0,
            0});
			this.RateUpDown.Minimum = new decimal(new int[] {
            5,
            0,
            0,
            65536});
			this.RateUpDown.Name = "RateUpDown";
			this.RateUpDown.Size = new System.Drawing.Size(89, 20);
			this.RateUpDown.TabIndex = 3;
			this.RateUpDown.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this.RateUpDown.ValueChanged += new System.EventHandler(this.RateUpDown_ValueChanged);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(311, 152);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(84, 13);
			this.label1.TabIndex = 4;
			this.label1.Text = "Speed multiplier:";
			// 
			// UpdateSpeedBtn
			// 
			this.UpdateSpeedBtn.Location = new System.Drawing.Point(285, 232);
			this.UpdateSpeedBtn.Name = "UpdateSpeedBtn";
			this.UpdateSpeedBtn.Size = new System.Drawing.Size(231, 62);
			this.UpdateSpeedBtn.TabIndex = 5;
			this.UpdateSpeedBtn.Text = "Update speed";
			this.UpdateSpeedBtn.UseVisualStyleBackColor = true;
			this.UpdateSpeedBtn.EnabledChanged += new System.EventHandler(this.UpdateSpeedEnabled);
			this.UpdateSpeedBtn.Click += new System.EventHandler(this.UpdateSpeedBtn_Click);
			// 
			// RangeLockCheckbox
			// 
			this.RangeLockCheckbox.Checked = true;
			this.RangeLockCheckbox.CheckState = System.Windows.Forms.CheckState.Checked;
			this.RangeLockCheckbox.Location = new System.Drawing.Point(355, 175);
			this.RangeLockCheckbox.Name = "RangeLockCheckbox";
			this.RangeLockCheckbox.Size = new System.Drawing.Size(90, 19);
			this.RangeLockCheckbox.TabIndex = 0;
			this.RangeLockCheckbox.Text = "Range lock";
			this.RangeLockCheckbox.UseVisualStyleBackColor = true;
			this.RangeLockCheckbox.CheckedChanged += new System.EventHandler(this.RangeLockCheckbox_CheckedChanged);
			// 
			// EditBtn
			// 
			this.EditBtn.Location = new System.Drawing.Point(12, 6);
			this.EditBtn.Name = "EditBtn";
			this.EditBtn.Size = new System.Drawing.Size(75, 23);
			this.EditBtn.TabIndex = 6;
			this.EditBtn.Text = "Edit";
			this.EditBtn.UseVisualStyleBackColor = true;
			this.EditBtn.Click += new System.EventHandler(this.EditBtn_Click);
			// 
			// EditGroup
			// 
			this.EditGroup.Controls.Add(this.AddBtn);
			this.EditGroup.Location = new System.Drawing.Point(85, -10);
			this.EditGroup.Margin = new System.Windows.Forms.Padding(0);
			this.EditGroup.Name = "EditGroup";
			this.EditGroup.Padding = new System.Windows.Forms.Padding(0);
			this.EditGroup.Size = new System.Drawing.Size(720, 49);
			this.EditGroup.TabIndex = 7;
			this.EditGroup.TabStop = false;
			this.EditGroup.Paint += new System.Windows.Forms.PaintEventHandler(this.GroupBoxPaint);
			// 
			// AddBtn
			// 
			this.AddBtn.Location = new System.Drawing.Point(8, 16);
			this.AddBtn.Name = "AddBtn";
			this.AddBtn.Size = new System.Drawing.Size(75, 23);
			this.AddBtn.TabIndex = 7;
			this.AddBtn.Text = "Add";
			this.AddBtn.UseVisualStyleBackColor = true;
			this.AddBtn.Click += new System.EventHandler(this.AddBtn_Click);
			// 
			// BtnGroup
			// 
			this.BtnGroup.Location = new System.Drawing.Point(12, 45);
			this.BtnGroup.Name = "BtnGroup";
			this.BtnGroup.Size = new System.Drawing.Size(776, 57);
			this.BtnGroup.TabIndex = 8;
			this.BtnGroup.TabStop = false;
			this.BtnGroup.Paint += new System.Windows.Forms.PaintEventHandler(this.GroupBoxPaint);
			// 
			// forceNormalBox
			// 
			this.forceNormalBox.AutoSize = true;
			this.forceNormalBox.Enabled = false;
			this.forceNormalBox.Location = new System.Drawing.Point(121, 256);
			this.forceNormalBox.Name = "forceNormalBox";
			this.forceNormalBox.Size = new System.Drawing.Size(111, 17);
			this.forceNormalBox.TabIndex = 9;
			this.forceNormalBox.Text = "Use normal speed";
			this.forceNormalBox.UseVisualStyleBackColor = true;
			this.forceNormalBox.CheckedChanged += new System.EventHandler(this.forceNormalBox_CheckedChanged);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 369);
			this.Controls.Add(this.forceNormalBox);
			this.Controls.Add(this.EditBtn);
			this.Controls.Add(this.RangeLockCheckbox);
			this.Controls.Add(this.UpdateSpeedBtn);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.RateUpDown);
			this.Controls.Add(this.RateTrackBar);
			this.Controls.Add(this.StatusLabel);
			this.Controls.Add(this.InjectBtn);
			this.Controls.Add(this.EditGroup);
			this.Controls.Add(this.BtnGroup);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.Name = "MainForm";
			this.ShowIcon = false;
			this.Text = "osu! Rate Changer";
			this.Load += new System.EventHandler(this.MainForm_Load);
			((System.ComponentModel.ISupportInitialize)(this.RateTrackBar)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.RateUpDown)).EndInit();
			this.EditGroup.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button InjectBtn;
		private System.Windows.Forms.Label StatusLabel;
		private System.Windows.Forms.TrackBar RateTrackBar;
		private System.Windows.Forms.NumericUpDown RateUpDown;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button UpdateSpeedBtn;
		private System.Windows.Forms.CheckBox RangeLockCheckbox;
		private System.Windows.Forms.Button EditBtn;
		private System.Windows.Forms.GroupBox EditGroup;
		private System.Windows.Forms.Button AddBtn;
		private System.Windows.Forms.GroupBox BtnGroup;
		private System.Windows.Forms.CheckBox forceNormalBox;
	}
}

