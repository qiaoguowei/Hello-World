#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <string>
#include <boost/scope_exit.hpp>
#include <sstream>

using namespace std;

int main()
{
    Json::Value root;
    Json::Reader reader;
    string filename = "./endpointDiskProtection.json";
    ifstream fin;
    std::stringstream buffer;


    fin.open(filename, std::ifstream::in);
    BOOST_SCOPE_EXIT(&fin)
    {
        if (fin.is_open())
        {
            fin.close();
        }
    }BOOST_SCOPE_EXIT_END

    buffer << fin.rdbuf();
    string file_content = buffer.str();

    if (!reader.parse(file_content, root))
    {
        cout << "json parse failed." << endl;
        return -1;
    }

    for (Json::Value::const_iterator iter = root["endpointDiskProtection"].begin();
            iter != root["endpointDiskProtection"].end();
            iter++)
    {
        std::cout << iter->asString() << std::endl;
    }
}
