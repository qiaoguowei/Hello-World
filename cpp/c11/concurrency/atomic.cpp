#include <iostream>
#include <string>
#include <atomic>
#include <future>
#include <thread>
#include <chrono>

using namespace std;

long data;
std::atomic<bool> readyFlag(false);

void provider()
{
    cout << "<return>" << endl;
    std::cin.get();

    data = 42;

    readyFlag.store(true);
}

void consumer()
{
    while (!readyFlag.load())
    {
        cout.put('.').flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    cout << "\nvalue : " << data << endl;
}

int main()
{
    auto p = std::async(std::launch::async, provider);
    auto c = std::async(std::launch::async, consumer);
}








