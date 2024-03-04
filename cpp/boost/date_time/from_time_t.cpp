#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

int main()
{
    time_t rawtm;

    time(&rawtm);
    boost::posix_time::ptime now = boost::posix_time::from_time_t(rawtm);
    cout << now << endl;

    std::string timeStr = boost::posix_time::to_iso_extended_string(now);
    cout << timeStr << endl;
}
