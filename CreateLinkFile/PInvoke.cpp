#include "stdafx.h"
#include <Windows.h>
#include <iostream>


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


struct MyStruct
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


DLLAPI TestStructArray(int* b)
{
	int index = 0;

	while (b[index] != 0)
	{
		MyStruct* f = (MyStruct*)(b[index]);

		//cout << "X: " << f->x << "   Y: " << f->y << "    Z: " << f->z << endl;

		index++;
	}


	//cout << "end!!!" << endl;

	return 0;

}