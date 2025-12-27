namespace TransformerCore.View
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            label4 = new Label();
            label5 = new Label();
            label6 = new Label();
            label7 = new Label();
            label8 = new Label();
            label9 = new Label();
            label10 = new Label();
            label11 = new Label();
            label12 = new Label();
            TotalHeightTextBox = new TextBox();
            TotalWidthTextBox = new TextBox();
            SideToothLengthTextBox = new TextBox();
            MedianToothLengthTextBox = new TextBox();
            ToothHeightTextBox = new TextBox();
            ToothStepLengthTextBox = new TextBox();
            ErrorMessageTextBox = new TextBox();
            label13 = new Label();
            ValidationButton = new Button();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 9);
            label1.Name = "label1";
            label1.Size = new Size(134, 15);
            label1.TabIndex = 0;
            label1.Text = "(1) Общая высота (мм)";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(261, 9);
            label2.Name = "label2";
            label2.Size = new Size(48, 15);
            label2.TabIndex = 1;
            label2.Text = "[8; 32.5]";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(261, 41);
            label3.Name = "label3";
            label3.Size = new Size(39, 15);
            label3.TabIndex = 3;
            label3.Text = "[4; 28]";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(12, 41);
            label4.Name = "label4";
            label4.Size = new Size(140, 15);
            label4.TabIndex = 2;
            label4.Text = "(2) Общая ширина (мм)";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(261, 103);
            label5.Name = "label5";
            label5.Size = new Size(57, 15);
            label5.TabIndex = 7;
            label5.Text = "[2.8; 10.5]";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(12, 103);
            label6.Name = "label6";
            label6.Size = new Size(190, 15);
            label6.TabIndex = 6;
            label6.Text = "(4) Длина бокового зубчика (мм)";
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new Point(261, 71);
            label7.Name = "label7";
            label7.Size = new Size(39, 15);
            label7.TabIndex = 5;
            label7.Text = "[4; 20]";
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new Point(12, 71);
            label8.Name = "label8";
            label8.Size = new Size(203, 15);
            label8.TabIndex = 4;
            label8.Text = "(3) Длина срединного зубчика (мм)";
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Location = new Point(261, 164);
            label9.Name = "label9";
            label9.Size = new Size(165, 15);
            label9.TabIndex = 11;
            label9.Text = "[5.2; 22], но не более, чем (1)";
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Location = new Point(12, 164);
            label10.Name = "label10";
            label10.Size = new Size(147, 15);
            label10.TabIndex = 10;
            label10.Text = "(6) Высота зубчиков (мм)";
            // 
            // label11
            // 
            label11.AutoSize = true;
            label11.Location = new Point(261, 132);
            label11.Name = "label11";
            label11.Size = new Size(48, 15);
            label11.TabIndex = 9;
            label11.Text = "[3.2; 12]";
            // 
            // label12
            // 
            label12.AutoSize = true;
            label12.Location = new Point(12, 132);
            label12.Name = "label12";
            label12.Size = new Size(173, 15);
            label12.TabIndex = 8;
            label12.Text = "(5) Длина шага зубчиков (мм)";
            // 
            // TotalHeightTextBox
            // 
            TotalHeightTextBox.Location = new Point(459, 6);
            TotalHeightTextBox.Name = "TotalHeightTextBox";
            TotalHeightTextBox.Size = new Size(100, 23);
            TotalHeightTextBox.TabIndex = 12;
            TotalHeightTextBox.TextChanged += DoubleTypeTextBox_TextChanged;
            // 
            // TotalWidthTextBox
            // 
            TotalWidthTextBox.Location = new Point(459, 38);
            TotalWidthTextBox.Name = "TotalWidthTextBox";
            TotalWidthTextBox.Size = new Size(100, 23);
            TotalWidthTextBox.TabIndex = 13;
            TotalWidthTextBox.TextChanged += DoubleTypeTextBox_TextChanged;
            // 
            // SideToothLengthTextBox
            // 
            SideToothLengthTextBox.Location = new Point(459, 100);
            SideToothLengthTextBox.Name = "SideToothLengthTextBox";
            SideToothLengthTextBox.Size = new Size(100, 23);
            SideToothLengthTextBox.TabIndex = 15;
            SideToothLengthTextBox.TextChanged += DoubleTypeTextBox_TextChanged;
            // 
            // MedianToothLengthTextBox
            // 
            MedianToothLengthTextBox.Location = new Point(459, 68);
            MedianToothLengthTextBox.Name = "MedianToothLengthTextBox";
            MedianToothLengthTextBox.Size = new Size(100, 23);
            MedianToothLengthTextBox.TabIndex = 14;
            MedianToothLengthTextBox.TextChanged += DoubleTypeTextBox_TextChanged;
            // 
            // ToothHeightTextBox
            // 
            ToothHeightTextBox.Location = new Point(459, 161);
            ToothHeightTextBox.Name = "ToothHeightTextBox";
            ToothHeightTextBox.Size = new Size(100, 23);
            ToothHeightTextBox.TabIndex = 17;
            ToothHeightTextBox.TextChanged += DoubleTypeTextBox_TextChanged;
            // 
            // ToothStepLengthTextBox
            // 
            ToothStepLengthTextBox.Location = new Point(459, 129);
            ToothStepLengthTextBox.Name = "ToothStepLengthTextBox";
            ToothStepLengthTextBox.Size = new Size(100, 23);
            ToothStepLengthTextBox.TabIndex = 16;
            ToothStepLengthTextBox.TextChanged += DoubleTypeTextBox_TextChanged;
            // 
            // ErrorMessageTextBox
            // 
            ErrorMessageTextBox.Location = new Point(158, 192);
            ErrorMessageTextBox.Name = "ErrorMessageTextBox";
            ErrorMessageTextBox.ReadOnly = true;
            ErrorMessageTextBox.Size = new Size(401, 23);
            ErrorMessageTextBox.TabIndex = 18;
            // 
            // label13
            // 
            label13.AutoSize = true;
            label13.Location = new Point(12, 195);
            label13.Name = "label13";
            label13.Size = new Size(140, 15);
            label13.TabIndex = 19;
            label13.Text = "Сообщение об ошибке:";
            // 
            // ValidationButton
            // 
            ValidationButton.Location = new Point(204, 228);
            ValidationButton.Name = "ValidationButton";
            ValidationButton.Size = new Size(151, 35);
            ValidationButton.TabIndex = 20;
            ValidationButton.Text = "Готово";
            ValidationButton.UseVisualStyleBackColor = true;
            ValidationButton.Click += ValidationButton_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(572, 275);
            Controls.Add(ValidationButton);
            Controls.Add(label13);
            Controls.Add(ErrorMessageTextBox);
            Controls.Add(ToothHeightTextBox);
            Controls.Add(ToothStepLengthTextBox);
            Controls.Add(SideToothLengthTextBox);
            Controls.Add(MedianToothLengthTextBox);
            Controls.Add(TotalWidthTextBox);
            Controls.Add(TotalHeightTextBox);
            Controls.Add(label9);
            Controls.Add(label10);
            Controls.Add(label11);
            Controls.Add(label12);
            Controls.Add(label5);
            Controls.Add(label6);
            Controls.Add(label7);
            Controls.Add(label8);
            Controls.Add(label3);
            Controls.Add(label4);
            Controls.Add(label2);
            Controls.Add(label1);
            Name = "Form1";
            Text = "Form1";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private Label label5;
        private Label label6;
        private Label label7;
        private Label label8;
        private Label label9;
        private Label label10;
        private Label label11;
        private Label label12;
        private TextBox TotalHeightTextBox;
        private TextBox TotalWidthTextBox;
        private TextBox SideToothLengthTextBox;
        private TextBox MedianToothLengthTextBox;
        private TextBox ToothHeightTextBox;
        private TextBox ToothStepLengthTextBox;
        private TextBox ErrorMessageTextBox;
        private Label label13;
        private Button ValidationButton;
    }
}
