#include <iostream>

using namespace std;

int main()
{
	int *a = new int;
	*a = 10;
	cout << *a << endl;
	delete a;
}
