#include <iostream>
#include <string>

using namespace std;

class A
{
public:
    A() {}
    ~A()
    {
        cout << "call desturcture." << endl;
    }
};

int main()
{
    int i = 0;
    while(1)
    {
        A a;
        if (i == 3)
            break;
        i++;
        continue;
    }
}
