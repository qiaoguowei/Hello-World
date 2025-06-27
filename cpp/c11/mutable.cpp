#include <iostream>
#include <string>

using namespace std;

class A
{
public:
    A(int m_a):a(m_a) {}
    ~A() {}

    void add() const
    {
        a += a;
    }

    void print() const
    {
        cout << "a = " << a << endl;
    }

private:
    mutable int a;
};

int main()
{
    A a(2);
    a.print();
    a.add();
    a.print();
}
