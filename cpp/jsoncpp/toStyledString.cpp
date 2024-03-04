#include <iostream>
#include <jsoncpp/json/json.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
#if 0
	string str_json = R"({"cloudApps" : ["111",      "222", "333"] })";
	Json::Value root;
	Json::Reader m_read;

	if (!m_read.parse(str_json, root))
	{
		cout << "json parse failed." << endl;
		return -1;
	}

	cout << root["cloudApps"].toStyledString() << endl;
#endif
	ifstream fin("./json_result.json", std::ios::binary);
	if (!fin)
	{
		cout << "open file failed." << endl;
		return -1;
	}

	stringstream ss;
	ss << fin.rdbuf();
	Json::Value root;
	Json::Reader m_read;

	if (!m_read.parse(ss.str(), root))
	{
		cout << "json parse failed." << endl;
		return -1;
	}

	cout << root["message"].toStyledString() << endl;
}







