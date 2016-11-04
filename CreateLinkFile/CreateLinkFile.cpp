// CreateLinkFile.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <Windows.h>
#include <shlobj.h>
#include <string>
#include <tchar.h>
#include <iostream>


using namespace std;

extern "C"  _declspec(dllexport) char* __stdcall MyTest(char* i);


char* __stdcall MyTest(char* a)
{

	for (size_t i = 0; i < 1024; i++)
	{
		a[i] = i;
	}

	return  a;

}
