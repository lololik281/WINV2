using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Drawing.Text;

namespace Clock
{
	public partial class FontDialog : Form
	{
		MainForm parent;
		Dictionary<string, string> d_fonts;
		//Словарь (Дерево) - это стуктура данных, которая хранит множество пар <Ключ - Значение>  <Key - Value>
		public Font Font { get; set; }  //Объявляем Автоствойства 'Font', типа 'Font';
		public string FontFile { get; set; }
		public NumericUpDown NUDFontSize { get => nudFontSize; }
		public FontDialog()
		{
			InitializeComponent();
			//LoadFonts();
			d_fonts = new Dictionary<string, string>();
			Traverse($"{Application.ExecutablePath}\\..\\..\\..\\Fonts");
			comboBoxFonts.Items.AddRange(d_fonts.Keys.ToArray());
		}
		public FontDialog(MainForm parent, string fontFile = "", decimal size = 32) : this()
		{
			this.parent = parent;
			this.FontFile = fontFile;
			comboBoxFonts.SelectedItem = FontFile.Split('\\').Last();
			nudFontSize.Value = size;
			if(comboBoxFonts.SelectedItem != null)ApplyFontExample();
			this.Font = labelExample.Font;
		}

		private void FontDialog_Load(object sender, EventArgs e)
		{
			this.Location = new Point(parent.Location.X - this.Width / 3, parent.Location.Y + 80);
			//if (comboBoxFonts.SelectedIndex == -1)
		}
		void Traverse(string path)
		{
			Console.WriteLine(path);
			LoadFonts(path, "*.ttf");
			LoadFonts(path, "*.otf");
			string[] directories = Directory.GetDirectories(path);
			for (int i = 0; i < directories.Length; i++)
				Traverse(directories[i]);
		}
		void LoadFonts()
		{
			Console.WriteLine(Application.ExecutablePath);
			Directory.SetCurrentDirectory($"{Application.ExecutablePath}\\..\\..\\..\\Fonts");
			Console.WriteLine(Directory.GetCurrentDirectory());
			//string[] files = Directory.GetFiles(Directory.GetCurrentDirectory());
			LoadFonts(Directory.GetCurrentDirectory(), "*.ttf");
			LoadFonts(Directory.GetCurrentDirectory(), "*.otf");
		}
		void LoadFonts(string path, string format)
		{
			string[] files = Directory.GetFiles(path, format);
			for (int i = 0; i < files.Length; i++)
			{
				d_fonts.Add(files[i].Split('\\').Last(), files[i]);
				//files[i] = files[i].Split('\\').Last();
			}
			//comboBoxFonts.Items.AddRange(files);
		}
		void ApplyFontExample()
		{
			PrivateFontCollection pfc = new PrivateFontCollection();
			pfc.AddFontFile(d_fonts[comboBoxFonts.SelectedItem.ToString()]);
			//pfc.AddFontFile(comboBoxFonts.SelectedItem.ToString());
			labelExample.Font = new Font(pfc.Families[0], (float)nudFontSize.Value);
		}
		private void comboBoxFonts_SelectedIndexChanged(object sender, EventArgs e)
		{
			ApplyFontExample();
		}

		private void nudFontSize_ValueChanged(object sender, EventArgs e)
		{
			ApplyFontExample();
		}

		private void buttonOK_Click(object sender, EventArgs e)
		{
			this.Font = labelExample.Font;
			FontFile = d_fonts[comboBoxFonts.SelectedItem.ToString()];
		}
	}
}
