#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

int doSomething(char c)
{
    std::default_random_engine dre(c);
    std::uniform_int_distribution<int> id(10, 1000);

    for (int i = 0; i < 10; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }

    return c;
}

int func1()
{
    return doSomething('.');
}

int func2()
{
    return doSomething('+');
}

int main()
{
    cout << "starting func1() in background and func2() in foreground:" << endl;
    std::future<int> result1(std::async(func1));

    int result2 = func2();

    int result = result1.get() + result2;

    cout << "\nresult of func1()+func2(): " << result << endl;
}

/*
 * result1.get()
 * 1.如果func1（）被async（）启动于一个分离线程中并且已结束，你会立刻获得其结果。
 * 2.如果func1（）被启动但尚未结束，get（）会引发停滞（block）待func1（）结束后获得结果。
 * 3.如果func1（）尚未启动，会被强迫启动如同一个同步调用；get（）会引发停滞直至产生结果。
 *
 * 你也可以强迫async（）绝不推延目标函数的执行，只要明确传入一个launch策略[2]用以指挥async（），告诉它当它被调用时应明确地以异步方式启动目标函数：
 * std::future<long> result1 = std::async(std::launch::async, func1);
 * 如果异步调用在此处无法实现，程序会抛出一个 std：：system_error异常（见4.3.1节第43页）并带差错码resource_unavailable_try_again，它相当于POSIX的errno EAGAIN 
 *
 * 你可以强制延缓执行,std::launch：deferred为发射策略传给async().下面的做法允许你延缓func1()直到你对f调用get()
 * std::future<...> f(std::async(std::launch::deferred, func1));
 *
 * */











