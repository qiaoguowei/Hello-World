#include <iostream>
#include <dirent.h>

using namespace std;

int main()
{
	int n;
	struct dirent **m_namelist;
	string dirp = "/home/qgw/program/cplusplus";

	if((n = scandir(dirp.c_str(), &m_namelist, NULL, alphasort)) == -1)
	{
		perror("scandir()");
		return -1;
	}
	string fname;
	for(int i = 0; i < n; i++)
	{
		fname = m_namelist[i]->d_name;
		cout << fname << endl;
	}
			
}
