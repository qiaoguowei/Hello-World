#include <iostream>
#include <string>

class A
{
public:
    A() {}
    void setValue(bool value)
    {
        flag = value;
    }

    bool getValue() const
    {
        return flag;
    }
private:
    bool flag;
};

int main()
{
    A a;
    std::cout << a.getValue() << std::endl;
}
