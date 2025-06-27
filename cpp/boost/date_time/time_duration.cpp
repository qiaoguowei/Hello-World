#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

using namespace std;

int main()
{
    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    cout << now << endl;
    boost::posix_time::time_duration seconds(0, 0, 120);
    now = now + seconds;
    cout << now << endl;

    boost::posix_time::time_duration seconds2(0, 0, 0);
    now = now + seconds2;
    cout << now << endl;

    boost::posix_time::ptime xxx = boost::posix_time::ptime();
    if (xxx.is_not_a_date_time())
    {
        cout << "1111" << endl;
    }
}
