#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;
extern char **environ;

int main()
{
    for (int i = 0; environ[i]; ++i)
    {
        std::cout << environ[i] << std::endl;
    }

	string m_env = "PATH";
	char *ret = getenv(m_env.c_str());
	if (ret == NULL)
	{
		perror("getenv");
		return -1;
	}
	string cur_env(ret);
	cout << cur_env << endl;

	if (cur_env.find("/home/qgw/bin") == string::npos)
	{
		string put_str = cur_env + ":/home/qgw/bin";
		cout << put_str << endl;
		if (setenv("PATH", put_str.c_str(), 1))
		{
			cout << "putenv failed." << endl;
			return -1;
		}
	}
    for (int i = 0; environ[i]; ++i)
    {
        std::cout << environ[i] << std::endl;
    }
	sleep(30);
}
