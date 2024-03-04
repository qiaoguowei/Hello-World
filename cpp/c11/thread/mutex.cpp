#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <boost/shared_ptr.hpp>
#include <chrono>
#include <functional>

//using namespace std;
//
void thread_cb(boost::shared_ptr<std::mutex>& mMutex)
{
    std::lock_guard<std::mutex> mLock(*mMutex);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "thread id : " << std::this_thread::get_id() << std::endl;
}

int main()
{
    boost::shared_ptr<std::mutex> mMutex;
    mMutex.reset(new std::mutex());
    std::thread th1(std::bind(thread_cb, std::ref(mMutex)));
    std::thread th2(std::bind(thread_cb, std::ref(mMutex)));

    th1.join();
    th2.join();
}
