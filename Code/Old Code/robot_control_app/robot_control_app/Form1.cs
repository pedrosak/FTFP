using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;


namespace robot_control_app
{
    public partial class Form1 : Form
    {
        static SerialPort arduinoPort;

        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            double test = M3trackBar.Value;
            test = Math.Round(test / 50.0, 1) * 50;
            M3trackBar.Value = (int)test; 
            M3Value.Text = M3trackBar.Value.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int M1speed = 0;
            int M3speed = 0;
            int M4speed = 0;
            M1speed = M1trackBar.Value;
            M3speed = M3trackBar.Value;
            M4speed = M4trackBar.Value;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1speed.ToString());
            arduinoPort.WriteLine(M3speed.ToString());
            arduinoPort.WriteLine(M4speed.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            M1trackBar.Value = 0;
            M3trackBar.Value = 0;
            M4trackBar.Value = 0;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1trackBar.Value.ToString());
            arduinoPort.WriteLine(M3trackBar.Value.ToString());
            arduinoPort.WriteLine(M4trackBar.Value.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();

        }

        private void M4trackBar_Scroll(object sender, EventArgs e)
        {
            double test = M4trackBar.Value;
            test = Math.Round(test / 50.0, 1) * 50;
            M4trackBar.Value = (int)test;
            M4Value.Text = M4trackBar.Value.ToString();
        }

        private void M3Value_Click(object sender, EventArgs e)
        {
            
        }

        private void M1Value_Click(object sender, EventArgs e)
        {
            
        }

        private void M1trackBar_Scroll(object sender, EventArgs e)
        {
            double test = M1trackBar.Value;
            test = Math.Round(test / 50.0, 1) * 50;
            M1trackBar.Value = (int)test;
            M1Value.Text = M1trackBar.Value.ToString();
        }

        private void M3Run_Click(object sender, EventArgs e)
        {
            int M3speed = 150;
            M1trackBar.Value = 0;
            M4trackBar.Value = 0;
            M3trackBar.Value = M3speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1trackBar.Value.ToString());
            arduinoPort.WriteLine(M3speed.ToString());
            arduinoPort.WriteLine(M4trackBar.Value.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void M4Run_Click(object sender, EventArgs e)
        {
            int M4speed = 150;
            M1trackBar.Value = 0;
            M3trackBar.Value = 0;
            M4trackBar.Value = M4speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1trackBar.Value.ToString());
            arduinoPort.WriteLine(M3trackBar.Value.ToString());
            arduinoPort.WriteLine(M4speed.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void M1Run_Click(object sender, EventArgs e)
        {
            int M1speed = 150;
            M3trackBar.Value = 0;
            M4trackBar.Value = 0;
            M1trackBar.Value = M1speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1speed.ToString());
            arduinoPort.WriteLine(M3trackBar.Value.ToString());
            arduinoPort.WriteLine(M4trackBar.Value.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();

        }

        private void button3_Click(object sender, EventArgs e)
        {
            int M1speed = 150;
            int M3speed = 150;
            M4trackBar.Value = 0;
            M1trackBar.Value = M1speed;
            M3trackBar.Value = M3speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1speed.ToString());
            arduinoPort.WriteLine(M3speed.ToString());
            arduinoPort.WriteLine(M4trackBar.Value.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void M1andM4_Click(object sender, EventArgs e)
        {
            int M1speed = 150;
            int M4speed = 150;
            M3trackBar.Value = 0;
            M1trackBar.Value = M1speed;
            M4trackBar.Value = M4speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1speed.ToString());
            arduinoPort.WriteLine(M3trackBar.Value.ToString());
            arduinoPort.WriteLine(M4speed.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void M3andM4_Click(object sender, EventArgs e)
        {
            int M3speed = 150;
            int M4speed = 150;
            M1trackBar.Value = 0;
            M3trackBar.Value = M3speed;
            M4trackBar.Value = M4speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1trackBar.Value.ToString());
            arduinoPort.WriteLine(M3speed.ToString());
            arduinoPort.WriteLine(M4speed.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void M1andM3R_Click(object sender, EventArgs e)
        {
            int M1speed = -150;
            int M3speed = -150;
            M4trackBar.Value = 0;
            M1trackBar.Value = M1speed;
            M3trackBar.Value = M3speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1speed.ToString());
            arduinoPort.WriteLine(M3speed.ToString());
            arduinoPort.WriteLine(M4trackBar.Value.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void M1andM4R_Click(object sender, EventArgs e)
        {
            int M1speed = -150;
            int M4speed = -150;
            M3trackBar.Value = 0;
            M1trackBar.Value = M1speed;
            M4trackBar.Value = M4speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1speed.ToString());
            arduinoPort.WriteLine(M3trackBar.Value.ToString());
            arduinoPort.WriteLine(M4speed.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void M3andM4R_Click(object sender, EventArgs e)
        {
            int M3speed = -150;
            int M4speed = -150;
            M1trackBar.Value = 0;
            M3trackBar.Value = M3speed;
            M4trackBar.Value = M4speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1trackBar.Value.ToString());
            arduinoPort.WriteLine(M3speed.ToString());
            arduinoPort.WriteLine(M4speed.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void M1runR_Click(object sender, EventArgs e)
        {
            int M1speed = -150;
            M3trackBar.Value = 0;
            M4trackBar.Value = 0;
            M1trackBar.Value = M1speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1speed.ToString());
            arduinoPort.WriteLine(M3trackBar.Value.ToString());
            arduinoPort.WriteLine(M4trackBar.Value.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void M3RunR_Click(object sender, EventArgs e)
        {
            int M3speed = -150;
            M1trackBar.Value = 0;
            M4trackBar.Value = 0;
            M3trackBar.Value = M3speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1trackBar.Value.ToString());
            arduinoPort.WriteLine(M3speed.ToString());
            arduinoPort.WriteLine(M4trackBar.Value.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void M4RunR_Click(object sender, EventArgs e)
        {
            int M4speed = -150;
            M1trackBar.Value = 0;
            M3trackBar.Value = 0;
            M4trackBar.Value = M4speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1trackBar.Value.ToString());
            arduinoPort.WriteLine(M3trackBar.Value.ToString());
            arduinoPort.WriteLine(M4speed.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void button3_Click_1(object sender, EventArgs e)
        {
            int M1speed = 100;
            int M3speed = 100;
            int M4speed = -100;
            M1trackBar.Value = M1speed;
            M3trackBar.Value = M3speed;
            M4trackBar.Value = M4speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1speed.ToString());
            arduinoPort.WriteLine(M3speed.ToString());
            arduinoPort.WriteLine(M4speed.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            int M1speed = -100;
            int M3speed = 100;
            int M4speed = 100;
            M1trackBar.Value = M1speed;
            M3trackBar.Value = M3speed;
            M4trackBar.Value = M4speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1speed.ToString());
            arduinoPort.WriteLine(M3speed.ToString());
            arduinoPort.WriteLine(M4speed.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            int M1speed = -100;
            int M3speed = -100;
            int M4speed = 100;
            M1trackBar.Value = M1speed;
            M3trackBar.Value = M3speed;
            M4trackBar.Value = M4speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1speed.ToString());
            arduinoPort.WriteLine(M3speed.ToString());
            arduinoPort.WriteLine(M4speed.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            int M1speed = 100;
            int M3speed = -100;
            int M4speed = -100;
            M1trackBar.Value = M1speed;
            M3trackBar.Value = M3speed;
            M4trackBar.Value = M4speed;
            arduinoPort = new SerialPort();

            arduinoPort.BaudRate = 9600;
            arduinoPort.PortName = "COM8";
            arduinoPort.Open();
            arduinoPort.WriteLine(M1speed.ToString());
            arduinoPort.WriteLine(M3speed.ToString());
            arduinoPort.WriteLine(M4speed.ToString());
            M1Value.Text = M1trackBar.Value.ToString();
            M3Value.Text = M3trackBar.Value.ToString();
            M4Value.Text = M4trackBar.Value.ToString();
            arduinoPort.Close();
        }
    }
}

