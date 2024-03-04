#include <iostream>
#include <functional>
#include <string>

using namespace std;
class B
{
public:
    typedef std::function<int(int, int)> cb;

    B(cb& otherFunc) : func(otherFunc) {}

    int callFunc(int a, int b)
    {
        return func(a, b);
    }

private:
    cb func;
};

class A
{
public:
    A() : m_num(1) {}

    int sum(int a, int b)
    {
        return a + b + m_num;
    }

    void add(int num)
    {
        m_num += num;
    }

    void bindFunc()
    {
        std::function<int(int, int)> func = std::bind(&A::sum, this, std::placeholders::_1, std::placeholders::_2);
        B b(func);
        add(10);
        add(10);
        add(10);
        cout << b.callFunc(1, 2) << endl;
    }

private:
    int m_num;
};


int main()
{
    A a;
    a.bindFunc();
}
