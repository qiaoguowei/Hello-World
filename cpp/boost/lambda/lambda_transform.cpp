#include <iostream>
#include <algorithm>
#include <map>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

int main()
{
    std::vector<char> vec;

    vec.push_back('A');
    vec.push_back('B');
    vec.push_back('C');
    vec.push_back('D');

    std::transform(vec.begin(), vec.end(), vec.begin(), std::tolower(boost::lambda::_1));

    for (const char& x : vec)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}
