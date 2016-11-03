#include <Util.h>



int main()
{
	cout << FileOperation::CreateLinkFile(L"D:\\我的常用软件\\SPY.exe", L"", L"C:\\Users\\Taylor Swift\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\123.lnk", L"D:\\我的常用软件\\SPY.exe");

	system("Pause");

	return 0;

}

