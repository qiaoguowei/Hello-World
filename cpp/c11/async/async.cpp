#include <iostream>
#include <future>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

/*
 * template <class Fn, class... Args>
 * future<typename result_of<Fn(Args...)>::type> async(launch policy, Fn&& fn, Args&&... args);
 * fn返回的值可以通过返回的future对象访问(通过调用其成员future::get)。
 *
 * launch::async 异步:启动一个新线程来调用fn(就好像一个线程对象是用fn和args作为参数构造的，并且访问返回的future的共享状态joins it)。
 * launch::deferred Deferred:对fn的调用被延迟，直到返回的future的共享状态被访问(使用wait或get)。此时，fn被调用，函数不再被认为是延迟的。当这个调用返回时，返回的future的共享状态就准备好了。
 * launch::async|launch::deferred 自动:该函数自动选择策略(在某个时刻)。这取决于系统和库的实现，它们通常针对系统中并发性的当前可用性进行优化。
 *
 * */

//a non-optimized way of checking for prime numbers:
bool is_prime (int x) 
{
    sleep(3);
    std::cout << "Calculating" << x << ". Please, wait...\n";
    for (int i = 2; i < x; ++i) 
        if (x % i == 0) 
            return false;
    return true;
}

int main ()
{
    srand(time(NULL));
    int num = rand();
    // call is_prime(313222313) asynchronously:
    std::future<bool> fut = std::async(launch::async, is_prime, num);
    //std::future<bool> fut = std::async(launch::async, is_prime, 5);

    // ...
    cout << "wait begin" << endl;
    bool ret = fut.get();      //调用future::get会阻塞线程，直到提供者准备好共享状态
                               //通过这种方式，两个线程可以通过一个等待另一个设置值来同步。
    cout << "wait end" << endl;

    if (ret) 
        std::cout << "It is prime!\n";
    else 
        std::cout << "It is not prime.\n";

    return 0;
}


