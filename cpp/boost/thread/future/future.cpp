#include <iostream>
#include <boost/thread/future.hpp>
#include <string>

int main()
{
    boost::thread::future<int> f1 = boost::thread::async([]() { return 123; });  // or any heavy computation
    boost::thread::future<std::string> f2 = f1.then([](future<int> f) { return f.get().to_string()}); // here .get() won't block;
    std::cout << "end" << std::endl;
}
