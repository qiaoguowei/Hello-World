#include <iostream>
#include <boost/dynamic_bitset.hpp>
//#include <boost/utility.hpp>

//using namespace boost;


int main()
{
	boost::dynamic_bitset<> db1;
	boost::dynamic_bitset<> db2(10);
	//boost::dynamic_bitset<> db3(0x16, BOOST_BINARY(10101));
	boost::dynamic_bitset<> db4(std::string("0100"));
//	boost::dynamic_bitset<> db5(db3);

	boost::dynamic_bitset<> db6;
	db6 = db4;

//	std::cout << std::hex << db5.to_ulong() << std::endl;
	std::cout << db4[0] << db4[1] << db4[2] << std::endl;
}
