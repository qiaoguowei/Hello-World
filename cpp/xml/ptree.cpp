#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>

namespace bp = boost::property_tree;

int main()
{
	bp::ptree json_writer;

	json_writer.put("scanStatus", "m_scan_status");
	json_writer.put("lastExeTime", "-1");
	json_writer.put("nextExeTime", "-1");
	json_writer.put("libVersion", 1);
	json_writer.put("status", "true");

	std::stringstream ss;
	bp::write_json(ss, json_writer);
	std::string str1 = ss.str();
	std::cout << str1 << std::endl;
}
