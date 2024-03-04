#include <iostream>
#include <functional>
#include <unistd.h>
#include <boost/asio.hpp>
#include <boost/system/system_error.hpp>
#include <chrono>

int m_flag;

void test1(const boost::system::error_code& ec)
{
    if(ec == boost::asio::error::operation_aborted)
        std::cout << "async_wait failed." << std::endl;
    std::cout << "hello asio" << std::endl;
}

void print(const boost::system::error_code& ec, boost::asio::steady_timer &t)
{
    if(ec == boost::asio::error::operation_aborted)
        std::cout << "async_wait failed." << std::endl;
    std::cout << "async_wait hello asio" << std::endl;
    t.expires_at(std::chrono::steady_clock::now() + std::chrono::seconds(10));
    t.async_wait(test1);
    sleep(1);
    //t.cancel();
    std::cout << "stop....." << std::endl;
    //t.cancel();
}

void test2()
{
    boost::asio::io_service io;
    boost::asio::steady_timer t(io, std::chrono::steady_clock::now() + std::chrono::seconds(2));
    std::function<void(const boost::system::error_code&)> func = std::bind(print, std::placeholders::_1, std::ref(t));

    t.async_wait(func);
    io.run();
    std::cout << "block???" << std::endl;
}

int main()
{
    test2();
}
