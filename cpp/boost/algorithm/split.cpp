#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <boost/algorithm/string.hpp>

//using namespace boost;
/*
 * 对于场景：string s = "123456"，用"3","4"切分，默认情况下（boost::token_compress_off），
 * 切分结果为12，空，56，注意，这里的空不是空格。而是"3"，"4"之间的空。如果不想要这个空，
 * 指定boost::token_compress_on就行了。
 *
 * boost::token_compress_on的意思就是说，以"3"，"4"，切分，当出现34的时候，就把34压缩成整体，用"34"切分。
 * */
void test1()
{
    std::string str = "SPE.2.CAEService.v1.";
    std::vector<std::string> interfaces;
    boost::split(interfaces, str, boost::is_any_of("."));
    for (auto &interface : interfaces)
    {
        if (interface.empty())
        {
            continue;
        }
        std::cout << interface << std::endl;
    }
    std::cout << "size(): " << interfaces.size() << std::endl;
}

int main()
{
#if 0
    std::string str = "Samus,Link.Zelda::Mario-Luigi+zelda";
    std::list<std::string> vc;
    boost::split(vc, str, boost::is_any_of(",.:-+"), boost::token_compress_on);
    //boost::split(vc, str, boost::is_any_of(",.:-+"));
    for(auto& x : vc)
    {
        std::cout << "[" << x << "] ";
    }
    std::cout << std::endl;
#else
    test1();
#endif
}
