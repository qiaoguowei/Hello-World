#include <iostream>
#include <jsoncpp/json/json.h>
#include <string>
#include <boost/filesystem.hpp>
#include <fstream>
#include <sstream>
#include <boost/scope_exit.hpp>

using namespace std;

int main()
{
	Json::Value root;
	Json::Reader reader;
	std::ifstream fin;
	std::stringstream buffer;
	string filename = "./json_result.json";

	if (!boost::filesystem::exists(filename))
	{
		cout << "the json file is not exists." << endl;
		return -1;
	}

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

	Json::Value config = root["data"]["deviceConfig"][0];
	for (Json::ValueIterator itor = config.begin(); itor != config.end(); itor++)
	{
		cout << itor.key().asString() << " : ";
		cout << config[itor.key().asString()] << endl;
	}
}













