using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TestForm
{
    public partial class PinvokeForm : Form
    {
        public static MyStruct global_ms = new MyStruct();


        public PinvokeForm()
        {
            InitializeComponent();
        }


        private void button_Number_Click(object sender, EventArgs e)
        {

            int sum = DllAPI.TestNumber(1, 1, 1, 1.1f, 2.2d
                                       , out byte b, out short s, out int i, out float f, out double d);

            sum.Print();

        }


        private void button_String_Click(object sender, EventArgs e)
        {

            StringBuilder buf = new StringBuilder();

            DllAPI.TestString("hahha", buf);

            buf.Print();

        }


        private void button_ByteArray_Click(object sender, EventArgs e)
        {
            //传送数据到 C++
            byte[] b = new byte[255];

            for (int i = 0; i < 255; i++)
            {
                b[i] = 100;
            }

            IntPtr p = Marshal.AllocHGlobal(255);

            Marshal.Copy(b, 0, p, 255);

            DllAPI.TestByteArray(p, out int t, out int len);

            Marshal.FreeHGlobal(p);

            //从C++获取数据到 C#

            byte[] temp = new byte[len];

            Marshal.Copy((IntPtr)t, temp, 0, len);

        }


        private void button_Struct_Click(object sender, EventArgs e)
        {
            MyStruct ms = new MyStruct()
            {
                x = 10,
                y = 20.2,
                z = "123"
            };


            int size = Marshal.SizeOf(typeof(MyStruct));

            IntPtr p = Marshal.AllocHGlobal(size);

            DllAPI.TestStruct(ms, p);

            //获取 C++ 创建的结构体

            MyStruct obj = (MyStruct)Marshal.PtrToStructure(p, typeof(MyStruct));

            Marshal.FreeHGlobal(p);

            //记得最后要释放C++申请的内存

        }


        private void button_StructArray_Click(object sender, EventArgs e)
        {
            //声明传出数据： 一个MyStruct数组

            const int len = 10000;

            MyStruct[] msarray = new MyStruct[len];

            int size = Marshal.SizeOf(typeof(MyStruct));

            IntPtr[] t = new IntPtr[len];  //初始化 拥有所有数据的指针数组   

            for (int i = 0; i < len; i++)
            {

                msarray[i] = new MyStruct()   //初始化 传出数据数组
                {
                    x = i,
                    y = 10.0 * i,
                    z = "Index : " + i
                };

                t[i] = Marshal.AllocHGlobal(size);      //在非托管内存中为传出数据分配内存

                Marshal.StructureToPtr(msarray[i], t[i], false);   //将托管内存中的数据依次拷贝到刚分配的非托管内存中

            }

            int[] sendData = new int[len + 1];  //初始化传出数据的指针数组，相当于将刚刚在非托管内存中分配的内存的地址以int数组的形式传递给C++

            for (int i = 0; i < len; i++)
            {
                sendData[i] = (int)t[i];
            }

            var sendPtr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(int)) * (len + 1));  //在非托管内存中分配传出指针数组空间

            sendData[len] = 0;   //将数组最后一位置0，使C++可以计算数组的长度

            Marshal.Copy(sendData, 0, sendPtr, len + 1);  //将传出指针数组拷贝到刚刚分配的非托管内存中


            DllAPI.TestStructArray(sendPtr);  //将上面的非托管内存的指针传递到C++


            //下面删除刚刚在非托管内存中分配的内存

            for (int i = 0; i < len; i++)
                Marshal.FreeHGlobal(t[i]);

            Marshal.FreeHGlobal(sendPtr);

            ////////////////////////////////////  传送数据完成  /////////////////////////////////////////////


        }




    }



    class DllAPI
    {

        //数字s  C# -> C++ 可以直接传入  ；  C++ -> C#  C++ 传出时数字要声明成引用，C#接受时必须使用 out  注意！ C++中long 即是 c# 中int
        [DllImport("PInvoke.dll", EntryPoint = "TestNumber")]
        public static extern int TestNumber(byte b, short s, int i, float f, double d
                                            , out byte _b, out short _s, out int _i, out float _f, out double _d);

        //String :  C# -> C++ C#直接传入string，C++用char* 接受即可  ；  C++ -> C#  C++定义char* 传出，C# 用StringBulider接受 
        //                                                           相当于C# 分配了字符串内存后C++直接使用了
        [DllImport("PInvoke.dll", EntryPoint = "TestString")]
        public static extern int TestString(string text, StringBuilder content);


        //Byte数组 :  
        //C#传数组到C++时必须传入IntPtr，接受参数类型为Byte*。C#必须先在非托管内存中分配内存：Marshal.AllocHGlobal()，然后调用Marshal.Copy把C#数组数据传送到刚才分配的非托管内存中。
        //C++数组传送到C#时传出数组指针：out int 数组地址指针。C#接受到int类型的内存地址后转化成IntPtr，然后Marshal.Copy将非托管内存中的数组数据拷贝到C#中，这里要非常注意C++要将数组的长度一起传到C#中，以使C#可以分配合适的内存
        //注意！！！如果C++传出的数据时在堆上分配的内存时，一定要留出接口让C#调用以释放该内存
        [DllImport("PInvoke.dll", EntryPoint = "TestByteArray")]
        public static extern int TestByteArray(IntPtr b, out int t, out int len);


        //C# -> C++ 直接传入结构体  ;   C++ -> C# 传出一个结构体指针到C#，C#分配托管内存，调用PtrToStructure转换成结构体类型
        [DllImport("PInvoke.dll", EntryPoint = "TestStruct")]
        public static extern int TestStruct(MyStruct ms_out, IntPtr p);


        [DllImport("PInvoke.dll", EntryPoint = "TestStructArray")]
        public static extern int TestStructArray(IntPtr p);


        /// <summary>
        /// 将非托管内存转化为C#的结构对象
        /// </summary>
        /// <param name="bytes"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        public static object BytesToStruct(byte[] bytes, Type type)
        {
            int size = Marshal.SizeOf(type);//Get size of the struct or class.            
            if (bytes.Length < size)
            {
                return null;
            }
            IntPtr structPtr = Marshal.AllocHGlobal(size);//Allocate memory space of the struct or class.   
            Marshal.Copy(bytes, 0, structPtr, size);//Copy byte array to the memory space.  
            object obj = Marshal.PtrToStructure(structPtr, type);//Convert memory space to destination struct or class.           
            Marshal.FreeHGlobal(structPtr);//Release memory space.      
            return obj;
        }


    }


    public struct MyStruct
    {

        /// int
        public int x;

        /// double
        public double y;

        /// char*
        public string z;

    }


    public static class Util
    {
        public static void Print(this int value)
        {
            Console.WriteLine(value);
        }

        public static void Print(this string value)
        {
            Console.WriteLine(value);
        }

        public static void Print(this StringBuilder value)
        {
            Console.WriteLine(value.ToString());
        }

    }



}
