#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
//#include <algorithm>
#include <string>

int main()
{
    boost::posix_time::ptime pNow(boost::posix_time::microsec_clock::local_time());
    std::string sNow = to_iso_extended_string(pNow);
    std::cout << sNow << std::endl;

    sNow.replace(10, 1, " ");
    std::cout << sNow << std::endl;
}
