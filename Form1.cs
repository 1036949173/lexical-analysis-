using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            richTextBox2.Clear();
            string s = richTextBox1.Text;
            File.WriteAllText("G:\\vc++\\2017new\\ConsoleApplication179编译原理作业1\\ConsoleApplication179编译原理作业1\\in.txt", s);

            System.Diagnostics.ProcessStartInfo myStartInfo = new System.Diagnostics.ProcessStartInfo();
            myStartInfo.FileName = "G:\\vc++\\2017new\\ConsoleApplication179编译原理作业1\\Debug\\ConsoleApplication179编译原理作业1.exe";
            System.Diagnostics.Process myProcess = new System.Diagnostics.Process();
            myProcess.StartInfo = myStartInfo;
            myProcess.Start();
            myProcess.WaitForExit(); //等待程序退出 
 

            /*ProcessStartInfo info = new ProcessStartInfo();
            info.FileName = @"G:\\vc++\\2017new\\ConsoleApplication179编译原理作业1\\Debug\\ConsoleApplication179编译原理作业1.exe";
            info.Arguments = "";
            info.WindowStyle = ProcessWindowStyle.Minimized;
            Process pro = Process.Start(info);
            pro.WaitForExit();*/

            string[] lines = File.ReadAllLines("G:\\vc++\\2017new\\ConsoleApplication179编译原理作业1\\ConsoleApplication179编译原理作业1\\out.txt", System.Text.Encoding.GetEncoding("gb2312"));
            // 在textBox中显示文件内容
            foreach (string line in lines)
            {
                richTextBox2.AppendText(line + Environment.NewLine);
            }
        }

        private void richTextBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
