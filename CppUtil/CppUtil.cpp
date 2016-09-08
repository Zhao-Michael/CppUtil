#include <Util.h>
#include <Any.h>
#include <vector>

vector<Any> mList;


int main()
{

	int i = 110;
	string s = "";
	double d = 1.765;
	long l = 1290894;


	mList.push_back(i);

	mList.push_back(s);

	mList.push_back(d);

	mList.push_back(l);






	cout << mList[0].cast_type<int>() << endl;




	system("Pause");

	return 0;

}

