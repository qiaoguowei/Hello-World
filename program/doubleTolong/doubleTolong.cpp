#include <iostream>
#include <string>

using namespace std;
union Double2Long
{
    double f;
    uint64_t t;
} u;

uint64_t double2long()
{

    double x = 1.2345;

    Double2Long u;
    u.f = x;
    cout << u.t << endl;

    return u.t;
}

int main()
{
    uint64_t longNum = double2long();
    Double2Long u;
    u.t = longNum;
    cout << u.f << endl;
}
