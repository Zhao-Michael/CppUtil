#pragma once


#include <stdio.h>
#include <tchar.h>
#include <iostream>

#include <string>
#include <strstream>
#include <fstream>
#include <string.h>
#include <list>
#include <map>

#include <process.h>
#include <Windows.h>
#include <Tlhelp32.h>




using namespace std;

namespace StringConverter
{

	static map<char, int> map_char_int = {
		{ '1', 1 },
		{ '2', 2 },
		{ '3', 3 },
		{ '4', 4 },
		{ '5', 5 },
		{ '6', 6 },
		{ '7', 7 },
		{ '8', 8 },
		{ '9', 9 },
	};

	static map<int, char> map_int_char = {
		{ 1, '1' },
		{ 2, '2' },
		{ 3, '3' },
		{ 4, '4' },
		{ 5, '5' },
		{ 6, '6' },
		{ 7, '7' },
		{ 8, '8' },
		{ 9, '9' },
	};


	static string WChar2String(const wchar_t* wide)
	{
		wstring wstrValue(wide);

		string strValue;

		strValue.assign(wstrValue.begin(), wstrValue.end());  // convert wstring to string

		return strValue;
	}


	static LPWSTR String2WChar(const std::string & s)
	{
		int dwLen = strlen(s.c_str()) + 1;
		int nwLen = MultiByteToWideChar(CP_ACP, 0, s.c_str(), dwLen, NULL, 0);//算出合适的长度
		LPWSTR lpszPath = new WCHAR[dwLen];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), dwLen, lpszPath, nwLen);
		return lpszPath;

	}


	static long long Str2Num(string str)
	{
		long long sum = 0;

		for (size_t i = 1; i <= str.length(); i++)
		{
			sum += pow(10, str.length() - i)*map_char_int[str[i - 1]];
		}

		return sum;
	}

	static string Num2Str(long long num)
	{
		char str[100];

		sprintf_s(str, "%lld", num);

		string s(str);

		return s;
	}


	static LPWSTR IntToLPWSTR(long long n)
	{
		strstream ss;
		string s;
		ss << n;
		ss >> s;

		int dwLen = strlen(s.c_str()) + 1;
		int nwLen = MultiByteToWideChar(CP_ACP, 0, s.c_str(), dwLen, NULL, 0);//算出合适的长度
		LPWSTR lpszPath = new WCHAR[dwLen];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), dwLen, lpszPath, nwLen);
		return lpszPath;
	}


	static LPCWSTR stringToLPCWSTR(std::string orig)	{		size_t origsize = orig.length() + 1;		const size_t newsize = 100;		size_t convertedChars = 0;		wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));		mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);		return wcstring;	}

}



//************************************
// Method:    获取当前系统所有进程名
// FullName:  GetCurrentProcesses
// Access:    public static 
// Returns:   std::list<std::string>
// Qualifier:
//************************************
static list<string> GetCurrentProcesses()
{
	list<string> list;

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE) return list;

	PROCESSENTRY32 pe32;

	pe32.dwSize = sizeof(PROCESSENTRY32);

	BOOL bMore = Process32First(hProcessSnap, &pe32);

	while (bMore) {

		bMore = Process32Next(hProcessSnap, &pe32);

		string str = StringConverter::WChar2String(pe32.szExeFile);

		list.push_back(str);

	}

	CloseHandle(hProcessSnap);

	return list;

};