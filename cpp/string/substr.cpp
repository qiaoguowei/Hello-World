#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void test1()
{
	std::string str1 = "abcdefghigklmnopqistuvwxyz";

	std::string str2 = str1.substr(8, 10);
    std::string str3 = str1.substr(8);

	std::cout << str1 << std::endl;
	std::cout << str2 << std::endl;
	std::cout << str3 << std::endl;
#if 0
    std::string path = "/opt/skyguard/ucs/var/fpdb/filter";
    std::string tmp_path = path.substr(strlen("/opt/skyguard/ucs/var/fpdb"));
    std::cout << tmp_path  << std::endl;
#endif

    std::string path = "/opt/skyguard/ucs/var/fpdb/filter";
    std::string tmp_path = path.substr(strlen("/opt/skyguard/ucs/var/fpdb"));
    std::cout << tmp_path  << std::endl;
}

void test2()
{
    string process = "111,222,333,444,";
    cout << process << endl;
    process = process.substr(0, process.size() - 1);
    cout << process << endl;
}

void test3()
{
    string mpath = "1534128927#\\\\qafiles.skyguardmis.com\\QAFiles\\刘孝运\\客户的pst\\archive - 副本.pst\\收件箱\\转发: 数据泄露防护系统采购项目【商务谈判】";

    auto pos = mpath.find("#");
    if (pos != string::npos)
    {
        mpath = mpath.substr(pos+1);
    }

    cout << mpath << endl;
}

void test4()
{
    std::string str = "Unknown.eml|||Unknown.txt";
    std::string::size_type pos = str.find("|||");
    if (pos != std::string::npos)
    {
        std::string new_str = str.substr(0, pos);
        std::cout << new_str << std::endl;
    }
}

int main()
{
    test1();
}

