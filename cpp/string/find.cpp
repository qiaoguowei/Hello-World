#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <deque>

using namespace std;

void test1()
{
	std::string backupFile = "/opt/skyguard/download/backup/tmp_backup_MQj8in/SPE-V1-20220109010009179818.tar.gz";
	int beginStr = backupFile.find_last_of('/', std::string::npos); //第二个参数默认std::string::npos
	int endStr = backupFile.find_first_of('.', 0);
	std::cout << beginStr << ", " << endStr << std::endl;
	std::string saveName = backupFile.substr(beginStr, endStr-beginStr);
	std::cout << saveName << std::endl;
}

void test2()
{
	std::string str1 = "deviceConfig[0].icapDebug";
	std::string::size_type pos = 0;
	std::string::size_type pre = 0;
	pos = str1.find_first_of(".[", pos);
	if (pos != string::npos)
	{
		if (str1[pos] == '[')
		{
			pre = pos;
			pos = str1.find(']', pos);
			pos++;
		}
	}
	string s = str1.substr(pre, pos - pre);
	cout << s << endl;
}

void path_split(const string& dir, deque<string>& vstr)
{
	string ss(dir);
	string::size_type pos = 0, prepos = 0;

	while ((pos = ss.find('/', prepos)) != string::npos)
	{
		//string s = ss.substr(prepos, pos-prepos);
		string s = ss.substr(0, pos);
		vstr.push_back(s);
		prepos = pos + 1;
	}

	if (!ss.substr(prepos).empty())
	{
		vstr.push_back(dir);
	}
}

void test3()
{
	char buf[256];
	memset(buf, 0, sizeof(buf));
	getcwd(buf, sizeof(buf)-1);
	string dir(buf);
	deque<string> vstr;
	path_split(dir, vstr);

	for (const auto& x : vstr)
	{
		cout << x << endl;
	}
}

int main()
{
	test1();
}
