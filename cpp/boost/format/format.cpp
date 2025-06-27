#include <iostream>
#include <string>
#include <boost/format.hpp>

void test1()
{
    std::cout << boost::format("\nUsage:\n%6tDSAUtil set <file_name>\n") << std::endl;
}

void test2()
{
    int m_dsaid = 1;
    boost::format topic = boost::format("AGGS.%1%.internal.v1") %m_dsaid;
    std::cout << topic.str() << std::endl;
}

<<<<<<< HEAD
void test3()
{
    std::string client_id = "7a6ed187-920a-430c-8dfd-9b36be225613";
    std::string client_secret = "VrZ8Q~jVb0Sstct7_vi1Qz5pSx2-TFiNzKasbcp_";
    boost::format m_postdata = boost::format("client_id=%s&scope=https\%3A\%2F\%2Foutlook.office365.com\%2F.default&&client_secret=%s&gr ant_type=client_credentials") % client_id.c_str() % client_secret.c_str();

    std::cout << m_postdata.str() << std::endl;
}

int main()
{
    test3();
=======
int main()
{
    test2();
>>>>>>> 4adb3f20a968faa466b0157e6da162535c178879
}
