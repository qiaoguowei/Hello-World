#include <iostream>
#include <jsoncpp/json/json.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	//string str_json = "{\"cloudApps\" : \"\"}";
    ifstream fin("./json_result.json", std::ios::in | std::ios::binary);
    stringstream ss;
    ss << fin.rdbuf();
    string str_json = ss.str();
    fin.close();
	Json::Value root;
	Json::Reader m_read;

	if (!m_read.parse(str_json, root))
	{
		cout << "json parse failed." << endl;
		return -1;
	}

	if (root["cloudApps"].isNull())
	{
		cout << "cloudApps is null." << endl;
	}

    if (root["mixItem"].isNull())
    {
        cout << "mexItem is null." << endl;
    }
    if (root["mixItem"].isArray())
    {
        cout << "mexItem is array." << endl;
    }
}
