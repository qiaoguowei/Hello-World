#include <iostream>
#include <jsoncpp/json/json.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
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
    Json::Value result;
    result["type"] = root["data"]["deviceConfig"]["type"];
    cout << result.toStyledString() << endl;
    Json::Value result2;
    result2["deviceConfig"] = result;
    result2["deviceConfig"].clear();
    cout << result2.toStyledString() << endl;

}
