#ifndef _XMLPARSER_H
#define _XMLPARSER_H

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

//using namespace boost::property_tree;


class XmlParser
{
public:
	XmlParser();
	XmlParser(std::string path);
	template <typename datatype>
	void getValue(std::string node_path, datatype& data);
	
private:
	boost::property_tree::ptree pt;
};


#endif


