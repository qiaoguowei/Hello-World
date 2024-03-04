#include <iostream>

using namespace std;

int main()
{
	string str1 = "abcd";
	string str2 = "eeee";
	char *p1 = (char *)str1.c_str();
	char *p2 = p1;
	p1 = (char *)str2.c_str();

	cout << p1 << endl;
	cout << p2 << endl;
}
