#include <Util.h>
#include <Any.h>


int main()
{

	vector<int> vec = { 1,2,3,4,5,7,8,5 };


	for (size_t i = 0; i < 100000; i++)
	{
		ThreadManager::StartTask([&] {

			for each (auto & item in vec)
			{
				cout << item << endl;
			}

		});

		Sleep(100);

	}





	system("Pause");

}

