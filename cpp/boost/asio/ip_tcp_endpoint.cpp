#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <assert.h>

int main()
{
	boost::asio::ip::address addr;
	addr = addr.from_string("127.0.0.1");

	boost::asio::ip::tcp::endpoint ep(addr, 9001);
	assert(ep.address() == addr);
	assert(ep.port() == 9001);
}
