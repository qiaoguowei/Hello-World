#include <iostream>
#include <fnmatch.h>

using namespace std;

int main()
{
	string str1 = "incl*";
	string str2 = "include";

	int ret = fnmatch(str1.c_str(), str2.c_str(), 0);
	if(ret == 0)
		cout << "match success" << endl;
}
