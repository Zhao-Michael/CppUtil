namespace TestForm
{
    partial class PinvokeForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.button_Number = new System.Windows.Forms.Button();
            this.button_String = new System.Windows.Forms.Button();
            this.button_ByteArray = new System.Windows.Forms.Button();
            this.button_Struct = new System.Windows.Forms.Button();
            this.button_StructAray = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button_Number
            // 
            this.button_Number.Location = new System.Drawing.Point(31, 39);
            this.button_Number.Margin = new System.Windows.Forms.Padding(4);
            this.button_Number.Name = "button_Number";
            this.button_Number.Size = new System.Drawing.Size(145, 68);
            this.button_Number.TabIndex = 0;
            this.button_Number.Text = "Number";
            this.button_Number.UseVisualStyleBackColor = true;
            this.button_Number.Click += new System.EventHandler(this.button_Number_Click);
            // 
            // button_String
            // 
            this.button_String.Location = new System.Drawing.Point(31, 137);
            this.button_String.Name = "button_String";
            this.button_String.Size = new System.Drawing.Size(145, 68);
            this.button_String.TabIndex = 1;
            this.button_String.Text = "String";
            this.button_String.UseVisualStyleBackColor = true;
            this.button_String.Click += new System.EventHandler(this.button_String_Click);
            // 
            // button_ByteArray
            // 
            this.button_ByteArray.Location = new System.Drawing.Point(31, 235);
            this.button_ByteArray.Name = "button_ByteArray";
            this.button_ByteArray.Size = new System.Drawing.Size(145, 68);
            this.button_ByteArray.TabIndex = 1;
            this.button_ByteArray.Text = "Byte Array";
            this.button_ByteArray.UseVisualStyleBackColor = true;
            this.button_ByteArray.Click += new System.EventHandler(this.button_ByteArray_Click);
            // 
            // button_Struct
            // 
            this.button_Struct.Location = new System.Drawing.Point(31, 333);
            this.button_Struct.Name = "button_Struct";
            this.button_Struct.Size = new System.Drawing.Size(145, 68);
            this.button_Struct.TabIndex = 1;
            this.button_Struct.Text = "Struct";
            this.button_Struct.UseVisualStyleBackColor = true;
            this.button_Struct.Click += new System.EventHandler(this.button_Struct_Click);
            // 
            // button_StructAray
            // 
            this.button_StructAray.Location = new System.Drawing.Point(31, 431);
            this.button_StructAray.Name = "button_StructAray";
            this.button_StructAray.Size = new System.Drawing.Size(145, 68);
            this.button_StructAray.TabIndex = 1;
            this.button_StructAray.Text = "Struct Array";
            this.button_StructAray.UseVisualStyleBackColor = true;
            this.button_StructAray.Click += new System.EventHandler(this.button_StructArray_Click);
            // 
            // PinvokeForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(562, 540);
            this.Controls.Add(this.button_StructAray);
            this.Controls.Add(this.button_Struct);
            this.Controls.Add(this.button_ByteArray);
            this.Controls.Add(this.button_String);
            this.Controls.Add(this.button_Number);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "PinvokeForm";
            this.Text = "PInvokeForm";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_Number;
        private System.Windows.Forms.Button button_String;
        private System.Windows.Forms.Button button_ByteArray;
        private System.Windows.Forms.Button button_Struct;
        private System.Windows.Forms.Button button_StructAray;
    }
}

