#include <iostream>
#include <boost/system/system_error.hpp>
#include <functional>
#include <boost/asio.hpp>

int main()
{
	boost::asio::io_service io;
	boost::asio::signal_set sig(io, SIGINT, SIGUSR1);

	auto handler1 = 
		[] (const boost::system::error_code& ec, int n)
		{
			if(ec)
			{
				std::cout << ec.message() << std::endl;
				return ;
			}
			if(n != SIGINT)
				return ;

			std::cout << "handler recv = " << n << std::endl;
			std::cout << "do something" << std::endl;
		};

	typedef void(handler_type)(const boost::system::error_code&, int);

	std::function<handler_type> handler2 = 
		[&] (const boost::system::error_code& ec, int n)
		{
			if(n != SIGUSR1)
				return ;
			std::cout << "handler2 recv = " << n << std::endl;
			sig.async_wait(handler1);
			sig.async_wait(handler2);
		};

	sig.async_wait(handler1);
	sig.async_wait(handler2);

	io.run();
	std::cout << "io stoped." << std::endl;

	return 0;
}
