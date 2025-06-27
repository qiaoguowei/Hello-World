#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/function.hpp>

int main()
{
    //boost::function<int(int, int, int)> f = (int ret = 0; ret = boost::lambda::_1 + boost::lambda::_2 + boost::lambda::_3; return ret;);
    boost::function<int(int, int, int)> f = boost::lambda::_1 + boost::lambda::_2 + boost::lambda::_3;
    int num = f(1, 2, 3);
    std::cout << "num = " << num << std::endl;
}
