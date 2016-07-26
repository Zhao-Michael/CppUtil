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


#include  <direct.h>  
#include <Shlwapi.h>


#include <regex>


#pragma comment(lib,"Shlwapi.lib")

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


	static LPWSTR Int2LPWSTR(long long n)
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


	static LPCWSTR String2LPCWSTR(std::string orig)	{		size_t origsize = orig.length() + 1;		const size_t newsize = 100;		size_t convertedChars = 0;		wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));		mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);		return wcstring;	}


	static void replace_all(const std::string & str, const std::string & before, const std::string & after)
	{


	}

	static vector<string> splite(const string &str, const string & splite_char)
	{

		int pos = -1;

		string temp = str;

		while (int pos = temp.find(splite_char) <= temp.size())
		{


		}

	}

}



class Stopwatch
{
private:

	LARGE_INTEGER  nFreq;

	LARGE_INTEGER nBeginTime;

	LARGE_INTEGER nEndTime;

	unsigned long time;

public:

	Stopwatch()
	{
		QueryPerformanceFrequency(&nFreq);
	}

	void Start()
	{
		if (nFreq.QuadPart == NULL)
		{
			QueryPerformanceFrequency(&nFreq);
		}

		QueryPerformanceCounter(&nBeginTime);

	}


	//单位为毫秒
	double Stop()
	{
		if (nBeginTime.QuadPart == 0)
		{
			return 0;
		}

		QueryPerformanceCounter(&nEndTime);

		auto time = (nEndTime.QuadPart - nBeginTime.QuadPart)*1000.0 / nFreq.QuadPart;

		nBeginTime.QuadPart = 0;

		return time;

	}


	~Stopwatch() = default;



	static unsigned __int64 GetSystemTime()  //最小精度是 16ms
	{
		return GetTickCount64();
	}


};



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



class FileOperation
{

public:

	/*static bool CheckPath(const string & str)
	{

		regex pattern("^[A-Za-z]{1}:\\\\.*");

		string s = str.replace("", "");

		return regex_match(str.replace("", ""), pattern);

	}*/


	static string GetCurrDirectory()
	{

		char buffer[1000];

		getcwd(buffer, 1000);

		return string(buffer);

	}



	static bool MakeFile(const string & file)
	{

		ofstream fout(file);

		return fout.is_open();

	}



	static bool DirExist(const string & path)
	{

		return (chdir(path.c_str()) == 0);

	}



	static bool FileExist(const string & file)
	{

		struct stat buffer;

		return (stat(file.c_str(), &buffer) == 0);

	}



	static bool MakeDir(const string & path)
	{
		if (mkdir(path.c_str()) == 0)
		{
			return true;
		}
		else
		{


		}
	}



	static void DeleteDir(const string & path, bool deletechild = true)
	{

		rmdir(path.c_str());

	}



	static string GetParentPath(const string& file)
	{

		auto temp = StringConverter::String2WChar(file.c_str());

		PathRemoveFileSpec(temp);

		return StringConverter::WChar2String(temp);

	}





};