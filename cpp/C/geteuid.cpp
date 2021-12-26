#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main()
{
	cout << geteuid() << endl;//root 的用户识别码是0
	cout << getuid() << endl;

	return 0;
}
