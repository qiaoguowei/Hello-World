#include <iostream>
#include <algorithm>
#include <map>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

int main()
{
    std::map<int, std::string> mm;
    mm.insert(std::make_pair<int, std::string>(1, std::string("aaa")));
    mm.insert(std::make_pair<int, std::string>(2, std::string("bbb")));
    mm.insert(std::make_pair<int, std::string>(3, std::string("ccc")));
    mm.insert(std::make_pair<int, std::string>(4, std::string("ddd")));

    int num = 3;
    std::map<int, std::string>::iterator ret = std::find_if(mm.begin(), mm.end(),
            boost::lambda::bind(&std::map<int, std::string>::value_type::first, boost::lambda::_1) == num);

    if (ret != mm.end())
    {
        std::cout << "find it" << std::endl;
        std::cout << ret->first << ", " << ret->second << std::endl;
    }
}
