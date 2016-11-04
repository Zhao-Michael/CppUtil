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

namespace TestForm
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            char[] power2 = new char[1024];

            IntPtr power = Marshal.UnsafeAddrOfPinnedArrayElement(power2, 0);

            IntPtr ptr = API.MyTest(power);

            char[] ys = new char[1024];

            Marshal.Copy(ptr, ys, 0, 1024);

        }


    }

    class API
    {
        [DllImport("CreateLinkFile.dll", EntryPoint = "MyTest", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr MyTest(IntPtr i);


    }



}
