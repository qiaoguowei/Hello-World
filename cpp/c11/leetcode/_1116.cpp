#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <stdlib.h>

using namespace std;

class ZeroEvenOdd {
private:
    int n;
    int index;
    int flag;
    std::mutex m_mutex;
    std::condition_variable cond;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        this->index = 0;
        this->flag = 0;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i++)
        {
            std::unique_lock<std::mutex> mLock(m_mutex);
            while (flag)
            {
                cond.wait(mLock);
            }
            printNumber(0);
            index = i;
            flag = 1;
            cond.notify_all();
        }

        std::unique_lock<std::mutex> mLock(m_mutex);
        while (flag)
        {
            cond.wait(mLock);
        }
        flag = 2;
        cond.notify_all();
    }

    void even(function<void(int)> printNumber) {
        while (true)
        {
            std::unique_lock<std::mutex> mLock(m_mutex);
            while (flag != 1 || index % 2 == 1)
            {
                if (flag == 2)
                {
                    cond.notify_all();
                    exit(0);
                }
                cond.wait(mLock);
            }

            printNumber(index);
            flag = 0;
            cond.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while (true)
        {
            std::unique_lock<std::mutex> mLock(m_mutex);
            while (flag != 1 || index % 2 == 0)
            {
                if (flag == 2)
                {
                    cond.notify_all();
                    exit(0);
                }
                cond.wait(mLock);
            }

            printNumber(index);
            flag = 0;
            cond.notify_all();
        }
    }
};

void print(int n)
{
    cout << n;
}

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);
    ZeroEvenOdd z(num);
    thread t1(bind(&ZeroEvenOdd::zero, &z, print));
    thread t2(bind(&ZeroEvenOdd::even, &z, print));
    thread t3(bind(&ZeroEvenOdd::odd, &z, print));

    t1.join();
    t2.join();
    t3.join();
}






