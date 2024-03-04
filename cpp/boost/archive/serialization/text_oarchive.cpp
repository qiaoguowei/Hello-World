#include <boost/archive/text_oarchive.hpp>
#include <iostream>

int main()
{
    boost::archive::text_oarchive oa(std::cout);
    int i = 111;
    oa << i;
}
