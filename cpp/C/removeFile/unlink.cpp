#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
	string filename = "test_unlink";

	if (access(filename.c_str(), F_OK))
	{
		perror("access()");
		return -1;
	}

	if (unlink(filename.c_str()) != 0)
	{
		cout << "remove the file failed" << endl;
		return -1;
	}
	cout << "remove the file successfully" << endl;
	
}
