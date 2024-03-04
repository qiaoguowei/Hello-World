#include <iostream>
#include <boost/foreach.hpp>
#include <map>
#include <boost/typeof/typeof.hpp>

int main()
{
    std::map<int, std::string> mm;
    mm.insert(std::make_pair<int, std::string>(1, std::string("aaa")));
    mm.insert(std::make_pair<int, std::string>(2, std::string("bbb")));
    mm.insert(std::make_pair<int, std::string>(3, std::string("ccc")));
    mm.insert(std::make_pair<int, std::string>(4, std::string("ddd")));

    //BOOST_FOREACH((BOOST_AUTO(x, std::map<int, std::string>::value_type), mm)
#if 0
    std::pair<int, std::string> pa;
    BOOST_FOREACH(BOOST_AUTO(x, pa), mm)
    {
        std::cout << x.first << ", " << x.second << std::endl;
    }
#else
    typedef std::pair<int, std::string> tmp_pair;
    BOOST_FOREACH(tmp_pair x, mm)
    {
        std::cout << x.first << ", " << x.second << std::endl;
    }
#endif
}
