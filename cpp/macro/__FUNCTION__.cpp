#include <iostream>

class TestClass
{
public:
    TestClass()
        : num(0)
    {}

    void print()
    {
        std::cout << __FUNCTION__ << std::endl;
    }

private:
    int num;
};

void test()
{
    std::cout << __FUNCTION__ << std::endl;
}

int main()
{
    test();

    TestClass test_class;
    test_class.print();
}
