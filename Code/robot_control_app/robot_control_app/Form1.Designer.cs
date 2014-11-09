namespace robot_control_app
{
    partial class Form1
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
            this.label1 = new System.Windows.Forms.Label();
            this.M4trackBar = new System.Windows.Forms.TrackBar();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.M1trackBar = new System.Windows.Forms.TrackBar();
            this.M3trackBar = new System.Windows.Forms.TrackBar();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.M4Value = new System.Windows.Forms.Label();
            this.M3Value = new System.Windows.Forms.Label();
            this.M1Value = new System.Windows.Forms.Label();
            this.M3Run = new System.Windows.Forms.Button();
            this.M4Run = new System.Windows.Forms.Button();
            this.M1Run = new System.Windows.Forms.Button();
            this.M1andM3 = new System.Windows.Forms.Button();
            this.M1andM4 = new System.Windows.Forms.Button();
            this.M3andM4 = new System.Windows.Forms.Button();
            this.M1andM3R = new System.Windows.Forms.Button();
            this.M1andM4R = new System.Windows.Forms.Button();
            this.M3andM4R = new System.Windows.Forms.Button();
            this.M1runR = new System.Windows.Forms.Button();
            this.M3RunR = new System.Windows.Forms.Button();
            this.M4RunR = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.M4trackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.M1trackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.M3trackBar)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(115, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(22, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "M1";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // M4trackBar
            // 
            this.M4trackBar.LargeChange = 50;
            this.M4trackBar.Location = new System.Drawing.Point(26, 195);
            this.M4trackBar.Maximum = 255;
            this.M4trackBar.Minimum = -255;
            this.M4trackBar.Name = "M4trackBar";
            this.M4trackBar.Size = new System.Drawing.Size(200, 45);
            this.M4trackBar.SmallChange = 10;
            this.M4trackBar.TabIndex = 2;
            this.M4trackBar.TickFrequency = 50;
            this.M4trackBar.Scroll += new System.EventHandler(this.M4trackBar_Scroll);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(115, 96);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(22, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "M3";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(115, 179);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(22, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "M4";
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // M1trackBar
            // 
            this.M1trackBar.LargeChange = 50;
            this.M1trackBar.Location = new System.Drawing.Point(26, 45);
            this.M1trackBar.Maximum = 255;
            this.M1trackBar.Minimum = -255;
            this.M1trackBar.Name = "M1trackBar";
            this.M1trackBar.Size = new System.Drawing.Size(200, 45);
            this.M1trackBar.SmallChange = 10;
            this.M1trackBar.TabIndex = 6;
            this.M1trackBar.TickFrequency = 50;
            this.M1trackBar.Scroll += new System.EventHandler(this.M1trackBar_Scroll);
            // 
            // M3trackBar
            // 
            this.M3trackBar.LargeChange = 50;
            this.M3trackBar.Location = new System.Drawing.Point(26, 112);
            this.M3trackBar.Maximum = 255;
            this.M3trackBar.Minimum = -255;
            this.M3trackBar.Name = "M3trackBar";
            this.M3trackBar.Size = new System.Drawing.Size(200, 45);
            this.M3trackBar.SmallChange = 10;
            this.M3trackBar.TabIndex = 7;
            this.M3trackBar.TickFrequency = 50;
            this.M3trackBar.Scroll += new System.EventHandler(this.trackBar3_Scroll);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(257, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(90, 50);
            this.button1.TabIndex = 8;
            this.button1.Text = "GO";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(258, 68);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(89, 52);
            this.button2.TabIndex = 9;
            this.button2.Text = "STOP";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // M4Value
            // 
            this.M4Value.AutoSize = true;
            this.M4Value.Location = new System.Drawing.Point(224, 226);
            this.M4Value.Name = "M4Value";
            this.M4Value.Size = new System.Drawing.Size(13, 13);
            this.M4Value.TabIndex = 10;
            this.M4Value.Text = "0";
            // 
            // M3Value
            // 
            this.M3Value.AutoSize = true;
            this.M3Value.Location = new System.Drawing.Point(224, 154);
            this.M3Value.Name = "M3Value";
            this.M3Value.Size = new System.Drawing.Size(13, 13);
            this.M3Value.TabIndex = 11;
            this.M3Value.Text = "0";
            this.M3Value.Click += new System.EventHandler(this.M3Value_Click);
            // 
            // M1Value
            // 
            this.M1Value.AutoSize = true;
            this.M1Value.Location = new System.Drawing.Point(224, 55);
            this.M1Value.Name = "M1Value";
            this.M1Value.Size = new System.Drawing.Size(13, 13);
            this.M1Value.TabIndex = 12;
            this.M1Value.Text = "0";
            this.M1Value.Click += new System.EventHandler(this.M1Value_Click);
            // 
            // M3Run
            // 
            this.M3Run.Location = new System.Drawing.Point(353, 48);
            this.M3Run.Name = "M3Run";
            this.M3Run.Size = new System.Drawing.Size(75, 23);
            this.M3Run.TabIndex = 13;
            this.M3Run.Text = "M3 RUN";
            this.M3Run.UseVisualStyleBackColor = true;
            this.M3Run.Click += new System.EventHandler(this.M3Run_Click);
            // 
            // M4Run
            // 
            this.M4Run.Location = new System.Drawing.Point(353, 77);
            this.M4Run.Name = "M4Run";
            this.M4Run.Size = new System.Drawing.Size(75, 23);
            this.M4Run.TabIndex = 14;
            this.M4Run.Text = "M4 RUN";
            this.M4Run.UseVisualStyleBackColor = true;
            this.M4Run.Click += new System.EventHandler(this.M4Run_Click);
            // 
            // M1Run
            // 
            this.M1Run.Location = new System.Drawing.Point(353, 19);
            this.M1Run.Name = "M1Run";
            this.M1Run.Size = new System.Drawing.Size(75, 23);
            this.M1Run.TabIndex = 15;
            this.M1Run.Text = "M1 RUN";
            this.M1Run.UseVisualStyleBackColor = true;
            this.M1Run.Click += new System.EventHandler(this.M1Run_Click);
            // 
            // M1andM3
            // 
            this.M1andM3.Location = new System.Drawing.Point(258, 126);
            this.M1andM3.Name = "M1andM3";
            this.M1andM3.Size = new System.Drawing.Size(116, 31);
            this.M1andM3.TabIndex = 16;
            this.M1andM3.Text = "M1 and M3 (FWD)";
            this.M1andM3.UseVisualStyleBackColor = true;
            this.M1andM3.Click += new System.EventHandler(this.button3_Click);
            // 
            // M1andM4
            // 
            this.M1andM4.Location = new System.Drawing.Point(257, 170);
            this.M1andM4.Name = "M1andM4";
            this.M1andM4.Size = new System.Drawing.Size(116, 31);
            this.M1andM4.TabIndex = 17;
            this.M1andM4.Text = "M1 and M4 (FWD)";
            this.M1andM4.UseVisualStyleBackColor = true;
            this.M1andM4.Click += new System.EventHandler(this.M1andM4_Click);
            // 
            // M3andM4
            // 
            this.M3andM4.Location = new System.Drawing.Point(258, 217);
            this.M3andM4.Name = "M3andM4";
            this.M3andM4.Size = new System.Drawing.Size(115, 31);
            this.M3andM4.TabIndex = 18;
            this.M3andM4.Text = "M3 and M4 (FWD)";
            this.M3andM4.UseVisualStyleBackColor = true;
            this.M3andM4.Click += new System.EventHandler(this.M3andM4_Click);
            // 
            // M1andM3R
            // 
            this.M1andM3R.Location = new System.Drawing.Point(390, 126);
            this.M1andM3R.Name = "M1andM3R";
            this.M1andM3R.Size = new System.Drawing.Size(115, 31);
            this.M1andM3R.TabIndex = 19;
            this.M1andM3R.Text = "M1 and M3 (REV)";
            this.M1andM3R.UseVisualStyleBackColor = true;
            this.M1andM3R.Click += new System.EventHandler(this.M1andM3R_Click);
            // 
            // M1andM4R
            // 
            this.M1andM4R.Location = new System.Drawing.Point(390, 170);
            this.M1andM4R.Name = "M1andM4R";
            this.M1andM4R.Size = new System.Drawing.Size(115, 31);
            this.M1andM4R.TabIndex = 20;
            this.M1andM4R.Text = "M1 and M4 (REV)";
            this.M1andM4R.UseVisualStyleBackColor = true;
            this.M1andM4R.Click += new System.EventHandler(this.M1andM4R_Click);
            // 
            // M3andM4R
            // 
            this.M3andM4R.Location = new System.Drawing.Point(390, 217);
            this.M3andM4R.Name = "M3andM4R";
            this.M3andM4R.Size = new System.Drawing.Size(115, 31);
            this.M3andM4R.TabIndex = 21;
            this.M3andM4R.Text = "M3 and M4 (REV)";
            this.M3andM4R.UseVisualStyleBackColor = true;
            this.M3andM4R.Click += new System.EventHandler(this.M3andM4R_Click);
            // 
            // M1runR
            // 
            this.M1runR.Location = new System.Drawing.Point(449, 19);
            this.M1runR.Name = "M1runR";
            this.M1runR.Size = new System.Drawing.Size(75, 23);
            this.M1runR.TabIndex = 22;
            this.M1runR.Text = "M1 (REV)";
            this.M1runR.UseVisualStyleBackColor = true;
            this.M1runR.Click += new System.EventHandler(this.M1runR_Click);
            // 
            // M3RunR
            // 
            this.M3RunR.Location = new System.Drawing.Point(449, 48);
            this.M3RunR.Name = "M3RunR";
            this.M3RunR.Size = new System.Drawing.Size(75, 23);
            this.M3RunR.TabIndex = 23;
            this.M3RunR.Text = "M3 (REV)";
            this.M3RunR.UseVisualStyleBackColor = true;
            this.M3RunR.Click += new System.EventHandler(this.M3RunR_Click);
            // 
            // M4RunR
            // 
            this.M4RunR.Location = new System.Drawing.Point(449, 77);
            this.M4RunR.Name = "M4RunR";
            this.M4RunR.Size = new System.Drawing.Size(75, 23);
            this.M4RunR.TabIndex = 24;
            this.M4RunR.Text = "M4 (REV)";
            this.M4RunR.UseVisualStyleBackColor = true;
            this.M4RunR.Click += new System.EventHandler(this.M4RunR_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(532, 12);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(96, 51);
            this.button3.TabIndex = 25;
            this.button3.Text = "M1\\M3 (FWD) M4 (REV)";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click_1);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(532, 136);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(96, 48);
            this.button4.TabIndex = 26;
            this.button4.Text = "M3\\M4 (FWD) M1 (REV)";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(532, 77);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(96, 47);
            this.button5.TabIndex = 27;
            this.button5.Text = "M1\\M3 (REV) M4 (FWD)";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(532, 199);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(96, 49);
            this.button6.TabIndex = 28;
            this.button6.Text = "M3\\M4 (REV) M1 (FWD)";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(634, 271);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.M4RunR);
            this.Controls.Add(this.M3RunR);
            this.Controls.Add(this.M1runR);
            this.Controls.Add(this.M3andM4R);
            this.Controls.Add(this.M1andM4R);
            this.Controls.Add(this.M1andM3R);
            this.Controls.Add(this.M3andM4);
            this.Controls.Add(this.M1andM4);
            this.Controls.Add(this.M1andM3);
            this.Controls.Add(this.M1Run);
            this.Controls.Add(this.M4Run);
            this.Controls.Add(this.M3Run);
            this.Controls.Add(this.M1Value);
            this.Controls.Add(this.M3Value);
            this.Controls.Add(this.M4Value);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.M3trackBar);
            this.Controls.Add(this.M1trackBar);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.M4trackBar);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.M4trackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.M1trackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.M3trackBar)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TrackBar M1trackBar;
        private System.Windows.Forms.TrackBar M3trackBar;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label M4Value;
        private System.Windows.Forms.Label M3Value;
        private System.Windows.Forms.Label M1Value;
        private System.Windows.Forms.Button M3Run;
        private System.Windows.Forms.Button M4Run;
        private System.Windows.Forms.TrackBar M4trackBar;
        private System.Windows.Forms.Button M1Run;
        private System.Windows.Forms.Button M1andM3;
        private System.Windows.Forms.Button M1andM4;
        private System.Windows.Forms.Button M3andM4;
        private System.Windows.Forms.Button M1andM3R;
        private System.Windows.Forms.Button M1andM4R;
        private System.Windows.Forms.Button M3andM4R;
        private System.Windows.Forms.Button M1runR;
        private System.Windows.Forms.Button M3RunR;
        private System.Windows.Forms.Button M4RunR;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
    }
}

