#include <iostream>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>

int main()
{
	boost::uuids::random_generator rgen;
	std::cout << boost::uuids::to_string(rgen()) << std::endl;
}
