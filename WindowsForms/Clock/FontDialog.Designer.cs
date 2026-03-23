namespace Clock
{
	partial class FontDialog
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
			this.comboBoxFonts = new System.Windows.Forms.ComboBox();
			this.nudFontSize = new System.Windows.Forms.NumericUpDown();
			this.labelExample = new System.Windows.Forms.Label();
			this.buttonOK = new System.Windows.Forms.Button();
			this.buttonCancel = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.nudFontSize)).BeginInit();
			this.SuspendLayout();
			// 
			// comboBoxFonts
			// 
			this.comboBoxFonts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboBoxFonts.FormattingEnabled = true;
			this.comboBoxFonts.Location = new System.Drawing.Point(13, 13);
			this.comboBoxFonts.Name = "comboBoxFonts";
			this.comboBoxFonts.Size = new System.Drawing.Size(358, 21);
			this.comboBoxFonts.TabIndex = 0;
			this.comboBoxFonts.SelectedIndexChanged += new System.EventHandler(this.comboBoxFonts_SelectedIndexChanged);
			// 
			// nudFontSize
			// 
			this.nudFontSize.Location = new System.Drawing.Point(377, 14);
			this.nudFontSize.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
			this.nudFontSize.Minimum = new decimal(new int[] {
            20,
            0,
            0,
            0});
			this.nudFontSize.Name = "nudFontSize";
			this.nudFontSize.Size = new System.Drawing.Size(56, 20);
			this.nudFontSize.TabIndex = 1;
			this.nudFontSize.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			this.nudFontSize.Value = new decimal(new int[] {
            32,
            0,
            0,
            0});
			this.nudFontSize.ValueChanged += new System.EventHandler(this.nudFontSize_ValueChanged);
			// 
			// labelExample
			// 
			this.labelExample.AutoSize = true;
			this.labelExample.Font = new System.Drawing.Font("Microsoft Sans Serif", 32.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.labelExample.Location = new System.Drawing.Point(4, 37);
			this.labelExample.Name = "labelExample";
			this.labelExample.Size = new System.Drawing.Size(191, 51);
			this.labelExample.TabIndex = 2;
			this.labelExample.Text = "Example";
			// 
			// buttonOK
			// 
			this.buttonOK.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.buttonOK.Location = new System.Drawing.Point(273, 107);
			this.buttonOK.Name = "buttonOK";
			this.buttonOK.Size = new System.Drawing.Size(75, 23);
			this.buttonOK.TabIndex = 3;
			this.buttonOK.Text = "OK";
			this.buttonOK.UseVisualStyleBackColor = true;
			this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
			// 
			// buttonCancel
			// 
			this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonCancel.Location = new System.Drawing.Point(354, 107);
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size(75, 23);
			this.buttonCancel.TabIndex = 4;
			this.buttonCancel.Text = "Cancel";
			this.buttonCancel.UseVisualStyleBackColor = true;
			// 
			// FontDialog
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(441, 142);
			this.Controls.Add(this.buttonCancel);
			this.Controls.Add(this.buttonOK);
			this.Controls.Add(this.labelExample);
			this.Controls.Add(this.nudFontSize);
			this.Controls.Add(this.comboBoxFonts);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Name = "FontDialog";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "ChooseFont";
			this.Load += new System.EventHandler(this.FontDialog_Load);
			((System.ComponentModel.ISupportInitialize)(this.nudFontSize)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ComboBox comboBoxFonts;
		private System.Windows.Forms.NumericUpDown nudFontSize;
		private System.Windows.Forms.Label labelExample;
		private System.Windows.Forms.Button buttonOK;
		private System.Windows.Forms.Button buttonCancel;
	}
}