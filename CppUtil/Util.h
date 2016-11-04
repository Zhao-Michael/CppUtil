#pragma once


#include <stdio.h>
#include <tchar.h>
#include <iostream>

#include <string>
#include <strstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <list>
#include <map>

#include <process.h>
#include <Windows.h>
#include <Tlhelp32.h>


#include  <direct.h>  
#include <Shlwapi.h>

#include <shlobj.h>


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


	static string WChar2String(LPWSTR wide)
	{
		return WChar2String((wchar_t*)wide);
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


	static LPCWSTR String2LPCWSTR(std::string orig)
	{
		size_t origsize = orig.length() + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
		mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
		return wcstring;
	}


	static int Find_First(const string & str, const string & special_char) // debug: 0.015  release: 0.0004 ms
	{
		if (str.size() - special_char.size() < 0) return -1;

		int times = str.size() - special_char.size() + 1;

		auto str1 = str.data();

		auto str2 = special_char.data();


		for (size_t i = 0; i < times; i++)
		{
			if (str1[i] == str2[0])
			{
				if (special_char.size() == 1) return i;

				for (size_t j = 1; j < special_char.size(); j++)
				{
					if (str1[i + j] != str2[j])
					{
						break;
					}
					if (j == special_char.size() - 1) return i;
				}

			}
		}

		return -1;
	}


	static vector<string> Split(const string & str, const string & splite_char)  //debug: 0.1ms  release: 0.008ms
	{

		int pos = -1;

		vector<string> list;

		string temp = str;

		bool flag = true;

		while (flag)
		{
			int pos = Find_First(temp, splite_char);

			if (pos < temp.size())
			{
				list.push_back(temp.substr(0, pos));

				temp.erase(0, pos + splite_char.size());
			}
			else
			{
				flag = false;
			}
		}

		list.push_back(temp);

		return list;
	}


	static string Replace_All(std::string & str, const std::string & before, const std::string & after) //返回非引用结果 debug: 0.04ms  release: 0.004ms
	{
		int pos = -1;

		bool flag = true;

		while (flag)
		{
			int pos = Find_First(str, before);

			if (pos > -1)
			{
				str.erase(pos, before.size());

				str.insert(pos, after);
			}
			else
			{
				return str;
			}
		}
	}


	static bool StartWith(const string & str, const std::string & special_char)
	{
		if (str.size() < special_char.size()) return false;

		auto strPtr = str.data();

		auto charPtr = special_char.data();

		for (size_t i = 0; i < special_char.size(); i++)
		{
			if (strPtr[i] != charPtr[i])
			{
				return false;
			}
		}

		return true;

	}


	static bool EndWith(const std::string & str, const std::string & special_char)
	{

		if (str.size() < special_char.size()) return false;

		auto strPtr = str.data();

		auto charPtr = special_char.data();

		for (size_t i = 1; i <= special_char.size(); i++)
		{
			if (strPtr[str.size() - i] != special_char[special_char.size() - i])
			{
				return false;
			}
		}

		return true;

	}


	static bool Contains(const std::string & str, const std::string & special_char)
	{
		return Find_First(str, special_char) >= 0;
	}


	static string Upper(const string & str)
	{
		string temp;

		auto ptr = str.data();

		for (size_t i = 0; i < str.size(); i++)
		{
			if (ptr[i] > 'a' && ptr[i] < 'z')
			{
				temp += ptr[i] - 32;
			}
			else
			{
				temp += ptr[i];
			}
		}

		return temp;

	}


	static string Lower(const string & str)
	{
		string temp;

		auto ptr = str.data();

		for (size_t i = 0; i < str.size(); i++)
		{
			if (ptr[i] > 'A' && ptr[i] < 'Z')
			{
				temp += ptr[i] + 32;
			}
			else
			{
				temp += ptr[i];
			}
		}

		return temp;
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



//************************************
// Method:    执行非exe后缀名的程序
// FullName:  StartProcessNoEXE
// Access:    public static 
// Returns:   void
// Qualifier:
// Parameter: wchar_t * path 执行文件路径
// Parameter: wchar_t * arg  执行命令行参数
//************************************
static void StartProcessNoEXE(wchar_t* path, wchar_t* arg)
{
	STARTUPINFO si;

	PROCESS_INFORMATION pi;

	ZeroMemory(&pi, sizeof(pi));

	ZeroMemory(&si, sizeof(si));

	si.cb = sizeof(si);

	CreateProcess(path, arg, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

}




//************************************
// Method:    申请管理员权限执行EXE
// FullName:  StartProcessAsAdmin
// Access:    public static 
// Returns:   void
// Qualifier:
// Parameter: wchar_t * path 执行文件路径
// Parameter: wchar_t * arg  执行命令行参数
//************************************
static void StartEXEAsAdmin(wchar_t* path, wchar_t* arg)
{
	SHELLEXECUTEINFO info;

	info.cbSize = sizeof(info);

	info.fMask = SEE_MASK_NOCLOSEPROCESS;

	info.lpVerb = L"runas";

	info.nShow = SW_NORMAL;

	info.lpDirectory = NULL;

	info.lpParameters = arg;

	info.lpFile = path;

	ShellExecuteEx(&info);


}




class FileOperation
{

public:

	static bool CheckPath(const string & str)
	{

		string s_temp = str;

		regex pattern("^[A-Za-z]{1}:\\\\.*");

		StringConverter::Replace_All(s_temp, "/", "\\");

		return regex_match(s_temp, pattern);

	}


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



	static bool MakeDir(string & path, bool recursive = true)
	{

		if (!recursive) return (mkdir(path.c_str()) == 0);

		string t_path(StringConverter::Replace_All(path, "/", "\\"));

		if (DirExist(path))
		{
			if (mkdir(path.c_str()) == 0)
			{
				return true;
			}
			else
			{
				auto vec = StringConverter::Split(t_path, "\\");

				vector<string> vectorPath;

				for (size_t i = 1; i < vec.size(); i++)
				{
					auto p = vec[0] + "\\";

					for (size_t j = 0; j < i; j++)
					{
						p += vec[i];
					}

					vectorPath.push_back(p);
				}





				/*if (vec.size() <= 1) return false;

				for (size_t i = 1; i < vec.size(); i++)
				{
					string temp = vec[0];

					if (mkdir((temp + "\\").c_str()) != 0)
					{

					}
				}*/
			}
		}

	}



	static void DeleteDir(const string & path, bool recursive = true)
	{

		rmdir(path.c_str());

	}



	static string GetParentPath(const string& file)
	{

		auto temp = StringConverter::String2WChar(file.c_str());

		PathRemoveFileSpec(temp);

		return StringConverter::WChar2String(temp);

	}


	static string ReadTextAll(const string & file)
	{
		ifstream ifs(file);

		ostringstream out;

		out << ifs.rdbuf();

		ifs.close();

		return out.str();
	}



	static vector<string> GetAllParetDir(const string & path)
	{

		if (!CheckPath(path)) return vector<string>();

		auto vec = StringConverter::Split(path, "\\");

		vector<string> vectorPath;

		for (size_t i = 1; i < vec.size(); i++)
		{
			string p;

			for (size_t j = 0; j <= i; j++)
			{
				p += vec[j] + "\\" + "\\";
			}

			vectorPath.push_back(p.substr(0, p.size() - 2));

		}

		return vectorPath;
	}


	// szStartAppPath : 点击后启动的程序
	// szAddCmdLine : 传给main函数的lpCmdLine
	// szDestLnkPath : 快捷方式的保存路径
	// szIconPath : 快捷方式显示的图标
#ifdef _UNICODE
	typedef wstring tstring;
#else
	typedef string tstring;
#endif

	static bool CreateLinkFile(LPCTSTR szStartAppPath, LPCTSTR szAddCmdLine, LPCTSTR szDestLnkPath, LPCTSTR szIconPath)
	{
		HRESULT hr = CoInitialize(NULL);
		if (SUCCEEDED(hr))
		{
			IShellLink *pShellLink;
			hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pShellLink);
			if (SUCCEEDED(hr))
			{
				pShellLink->SetPath(szStartAppPath);
				tstring strTmp = szStartAppPath;
				int nStart = strTmp.find_last_of(_T("/\\"));
				pShellLink->SetWorkingDirectory(strTmp.substr(0, nStart).c_str());
				pShellLink->SetArguments(szAddCmdLine);
				if (szIconPath)
				{
					pShellLink->SetIconLocation(szIconPath, 0);
				}
				IPersistFile* pPersistFile;
				hr = pShellLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile);
				if (SUCCEEDED(hr))
				{
					hr = pPersistFile->Save(szDestLnkPath, FALSE);
					if (SUCCEEDED(hr))
					{
						return true;
					}
					pPersistFile->Release();
				}
				pShellLink->Release();
			}
			CoUninitialize();
		}
		return false;
	}

};