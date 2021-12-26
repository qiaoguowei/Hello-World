#include <iostream>
#include <locale>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

int main()
{
	boost::posix_time::time_facet *tf = new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S");
	std::stringstream ss;
	ss.imbue(std::locale(std::cout.getloc(), tf));
	ss << boost::posix_time::second_clock::local_time();
	cout << ss.str() << endl;

	delete tf;
}
