#include <iostream>
#include "XmlParser.h"

int main()
{
	XmlParser xp("./conf.xml");
	std::string str1;
	xp.getValue<std::string>("conf.theme", str1);
	std::cout << str1 << std::endl;
}
