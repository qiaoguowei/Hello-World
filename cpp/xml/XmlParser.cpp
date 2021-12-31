#include "XmlParser.h"
#include <iostream>

XmlParser::XmlParser()
{
}

XmlParser::XmlParser(std::string path)
{
	boost::property_tree::read_xml(path, pt);
}

template <typename datatype>
void XmlParser::getValue(std::string node_path, datatype& data)
{
	data = pt.get<datatype>(node_path.c_str());
}


