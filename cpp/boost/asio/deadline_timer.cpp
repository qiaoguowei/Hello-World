#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/system/system_error.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <functional>

using namespace std;

void func(boost::asio::deadline_timer &t)
{
    cout << 11111 << endl;

//std::function<void()> f = std::bind(func, std::ref(t));
    t.expires_at(t.expires_at() + boost::posix_time::seconds(2));
    t.async_wait(std::bind(func, std::ref(t)));
}

int main()
{
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
    std::function<void()> f = std::bind(func, std::ref(t));

    t.async_wait(std::bind(func, std::ref(t)));
    io.run();
    cout << "end...." << endl;
}
