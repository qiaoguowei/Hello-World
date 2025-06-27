#include <iostream>
#include <boost/date_time/local_time/local_time.hpp>

using namespace std;

int main()
{
    boost::posix_time::ptime pt = boost::posix_time::second_clock::local_time();
    pt -= boost::posix_time::hours(8);
    boost::local_time::time_zone_ptr time_zone(new boost::local_time::posix_time_zone("CST+8"));

    boost::local_time::local_date_time ldt(pt, time_zone);
    cout << ldt << endl;
}
