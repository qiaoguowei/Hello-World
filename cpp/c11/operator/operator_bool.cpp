#include <iostream>

class Foo
{
public:
    operator bool() const;
};

Foo::operator bool() const
{
    return true;
}

int main()
{
    Foo foo;
    if (foo)
    {
        std::cout << "true" << std::endl;
    }
}
