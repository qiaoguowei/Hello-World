#include <iostream>
#include <string>

using namespace std;

class A
{
public:
	A()
	{
		cout << "this is A's constructure." << endl;
	}

	//virtual ~A() = default;
    virtual ~A()
    {
        std::cout << "this is A's destructure." << std::endl;
    }
};

class B : public A
{
public:
	B()
    {
        std::cout << "this is B's constructure." << std::endl;
    }

	//~B() override = default;
    ~B()
    {
        std::cout << "this is B's destructure." << std::endl;
    }
};

int main()
{
	A *b = new B();
    delete b;
}
