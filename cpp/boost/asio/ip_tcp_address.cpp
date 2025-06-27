#include <iostream>
#include <assert.h>
#include <boost/asio/ip/tcp.hpp>

using namespace std;

void test1()
{
	boost::asio::ip::address addr;

	addr = addr.from_string("127.0.0.1");
	assert(addr.is_v4());
	std::cout << addr.to_string() << std::endl;
	addr = addr.from_string("ab::12:34:56");
	assert(addr.is_v6());
}

void test2()
{
    try
    {
    std::string hostName = "login.microsoftonline.com";
    auto ad = boost::asio::ip::address::from_string(hostName);
    if (ad.is_v6())
        cout << hostName << endl;
    else
        cout << hostName << endl;
    }
    catch (const std::exception &e)
    {
        cout << "throw: " << e.what() << endl;
    }
}

int main()
{
    test2();
}










