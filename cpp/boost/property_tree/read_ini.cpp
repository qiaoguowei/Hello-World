#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

using namespace std;

void m_write()
{
	boost::property_tree::ptree pt;
	//boost::property_tree::ini_parser::read_ini("./test.ini", pt);

	pt.put<std::string>("OVERLAY.OverlayFontName", "宋体");
	pt.put<std::string>("OVERLAY.AuthorName", "张三");
	pt.put<std::string>("Other.Name","nobody");
	
	boost::property_tree::ini_parser::write_ini("./test.ini", pt);
}

void m_read()
{
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini("./test.ini", pt);

	try
	{
		std::cout << pt.get<std::string>("OVERLAY.OverlayFontNames") << std::endl;
	}
	catch(exception &e)
	{
		cout << e.what() << endl;
	}
}

int main()
{
	m_read();
}
