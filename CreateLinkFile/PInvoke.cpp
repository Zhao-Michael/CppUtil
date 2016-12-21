#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>


using namespace std;

#define DLLAPI  extern "C"  _declspec(dllexport) int __stdcall


BYTE thedata[255];


DLLAPI TestNumber(BYTE z, short s, int i, float f, double d
	, BYTE & _z, short & _s, int & _i, float & _f, double & _d)
{
	_z = z;
	_s = s;
	_i = i;
	_f = f;
	_d = d;

	return  0;

}


DLLAPI TestString(char* text, char* content)
{
	cout << text << "  from C++" << endl;

	memcpy(content, text, strlen(text));

	return 0;
}


DLLAPI TestByteArray(BYTE* b, int & t, int & len)
{

	int index = 0;

	while (b[index] != 0)
	{
		index++;
	}

	cout << "Src Byte Length: " << index << endl;


	len = 1000;

	auto temp = new BYTE[len];

	memset(temp, 110, len);

	t = (int)temp;

	/*len = 255;

	memset(thedata, 120, len);

	t = (int)&thedata;*/

	return 0;

}


struct MyStruct  //传递结构时，结构中只能有简单类型，不能又复杂结构或类等
{
	int x;
	double y;
	char* z;
};


DLLAPI TestStruct(MyStruct ms, MyStruct & ptr)
{

	ptr.x = ms.x;
	ptr.y = ms.y;
	ptr.z = ms.z;

	return 0;

}


DLLAPI TestStructArray(int* _in, int & _out, int & _outCount)
{
	int index = 0;

	while (_in[index] != 0)
	{
		MyStruct* f = (MyStruct*)(_in[index]);

		cout << "X: " << f->x << "   Y: " << f->y << "    Z: " << f->z << endl;

		index++;
	}

	//下面传送数据到C#  注意 char* 传出时应该设置字符为 Unicode 结尾要手动添加\0
	_outCount = 100;

	int* _outPtr = new int[_outCount];

	MyStruct* mys = new MyStruct[_outCount];

	for (size_t i = 0; i < _outCount; i++)
	{
		MyStruct* t = new MyStruct();

		t->x = i; t->y = i * 100; t->z = new char[100];

		string ts = to_string(i);

		memcpy(t->z, ts.data(), ts.size());

		t->z[ts.size()] = '\0';

		_outPtr[i] = (int)t;

	}

	_out = (int)_outPtr;

	return 0;

}