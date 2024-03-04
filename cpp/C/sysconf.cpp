#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
	cout << sysconf(_SC_OPEN_MAX) << endl;
}
