#include <iostream>
#include <boost/typeof/typeof.hpp>

int main()
{
    std::string aa;
    BOOST_AUTO(&bb, aa);
    bb = "aaaaa";

    BOOST_AUTO(cc, aa);
    cc = "ccccc";

    std::string xx;
    BOOST_AUTO(dd, xx) = cc;

    std::cout << bb << std::endl;
    std::cout << aa << std::endl;
    std::cout << cc << std::endl;
    std::cout << dd << std::endl;


    std::string s1 = "111";
    BOOST_AUTO(&s2, dd) = s1;

    std::cout << "s1 = " << s1 << std::endl;
    std::cout << "s2 = " << s2 << std::endl;

    s2 = "222";
    std::cout << "s1 = " << s1 << std::endl;
    std::cout << "s2 = " << s2 << std::endl;
}
