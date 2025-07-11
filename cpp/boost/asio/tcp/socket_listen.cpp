
#include <boost/asio.hpp> 
#include <string> 

boost::asio::io_service io_service; 
boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 80); 
boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint); 
boost::asio::ip::tcp::socket sock(io_service); 
std::string data = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!"; 

void write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) 
{ 
} 

void accept_handler(const boost::system::error_code &ec) 
{ 
    if (!ec) 
    { 
        boost::asio::async_write(sock, boost::asio::buffer(data), write_handler); 
    } 
} 

int main() 
{ 
    acceptor.listen(); 
    acceptor.async_accept(sock, accept_handler); 
    io_service.run(); 
} 
