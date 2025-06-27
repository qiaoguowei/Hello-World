#include <iostream>
#include <string>
#include <future>
#include <mutex>

using namespace std;

std::mutex printMutex;

void print(const std::string& s)
{
    std::lock_guard<std::mutex> l(printMutex);
    for (char c : s)
    {
        cout.put(c);
    }
    cout << endl;
}

int main()
{
    auto f1 = std::async(std::launch::async, print, "Hello from a first thread");
    auto f2 = std::async(std::launch::async, print, "Hello from a second thread");
    print("Hello from a main thread");
}







