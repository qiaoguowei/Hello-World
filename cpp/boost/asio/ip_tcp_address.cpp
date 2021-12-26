#include <iostream>
#include <assert.h>
#include <boost/asio/ip/tcp.hpp>

int main()
{
	boost::asio::ip::address addr;

	addr = addr.from_string("127.0.0.1");
	assert(addr.is_v4());
	std::cout << addr.to_string() << std::endl;
	addr = addr.from_string("ab::12:34:56");
	assert(addr.is_v6());
}
