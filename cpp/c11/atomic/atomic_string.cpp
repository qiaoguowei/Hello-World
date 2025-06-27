#include <iostream>
#include <atomic>
#include <string>

int main()
{
    std::atomic<std::string> ss;

    ss = "aaa";
    std::cout << ss.load() << std::endl;
    ss.exchange("");
    if (ss.load().empty())
    {
        ss = "bbb";
        std::cout << ss.load() << std::endl;
    }
}
