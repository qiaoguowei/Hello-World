#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <functional>

using namespace std;

void doSomething(std::promise<std::string>& p)
{
    try
    {
        cout << "read char ('x' for exception): ";
        char c = cin.get();
        if (c == 'x')
            throw std::runtime_error(std::string("char ") + c + " read");

        std::string s = std::string("char ") + c + " processed";
        p.set_value(std::move(s));
    }
    catch (...)
    {
        p.set_exception(std::current_exception());
    }
}

int main()
{
    try
    {
        std::promise<std::string> p;
        std::thread t(doSomething, std::ref(p));
        t.detach();

        std::future<std::string> f(p.get_future());

        std::cout << "result: " << f.get() << std::endl;
    }
    catch (...)
    {
        cout << "EXCEPTION" << endl;
    }
}










