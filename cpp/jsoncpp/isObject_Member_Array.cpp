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
	string filename = "./json_result.json";
	ifstream fin;
	std::stringstream buffer;
	Json::Reader reader;
	Json::Value value;

	if (!boost::filesystem::exists(filename))
	{
		cout << "the json file is not exist." << endl;
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
	std::string file_content = buffer.str();

	try
	{
		if (!reader.parse(file_content, value))
		{
			cout << "json parse failed." << endl;
			return -1;
		}

		cout << value.isObject() << endl;
		cout << value.isArray() << endl;
		cout << value.isMember("deviceConfig") << endl;

		Json::Value preVal = value["data"]["deviceConfig"];
		cout << preVal[0].isObject() << endl;
		cout << preVal.isArray() << endl;
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
	}
}








