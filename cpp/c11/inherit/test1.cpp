#include <iostream>
#include <string>

using namespace std;

class A
{
public:
    A(){}
    virtual ~A(){}

    void start()
    {
        print();
    }
private:
    virtual void print()
    {
        cout << "this is A" << endl;
    }

};

class B : public A
{
public:
    B(){}
    ~B(){}
private:
    void print() override
    {
        cout << "this is B" << endl;
    }
};

int main()
{
    A *a = new B();
    a->start();
    A *a2 = new A();
    a2->start();
    delete a;
    delete a2;
}












