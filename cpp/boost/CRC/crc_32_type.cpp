#include <boost/crc.hpp>
#include <iostream>

using namespace std;

void test()
{
	string str = "my name is sss";
	boost::crc_32_type crc32;
	crc32.process_bytes(str.c_str(), str.size());
	cout << crc32() << endl;
}

int main()
{
	test();
}
