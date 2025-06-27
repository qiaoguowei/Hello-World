#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

//using namespace boost::property_tree;
namespace bp = boost::property_tree;

void m_read_xml()
{
    try
    {
        bp::ptree pt;
        bp::read_xml("./conf.xml", pt);

        if (pt.count("conf") > 0)
        {
            std::string str1 = pt.get<std::string>("conf.theme");
            std::cout << str1 << std::endl;
        }
        int num1 = pt.get<int>("conf.clock_style");
        int num2 = pt.get("conf.no_prop", 100); //the node is not exist in the conf.xml, get the defult value;

        std::cout << num1 << std::endl;
        std::cout << num2 << std::endl;

        auto child = pt.get_child("conf.urls");
        for(auto x : child)
        {
            std::cout << x.first << ", " << x.second.get_value<std::string>() << std::endl;
        }

        for(auto x : child)
        {
            std::cout << x.second.data() << std::endl;
        }
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void m_write_xml()
{
    try
    {
        bp::ptree pt;
        read_xml("./conf.xml", pt);

        pt.put("conf.theme", "Matrix Reloaded");
        pt.put("conf.clock_style", 12);
        pt.put("conf.gui", 0);

        pt.add("conf.urls.url", "http://www.url4.org");

        write_xml(std::cout, pt);
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    m_read_xml();
}




