#include <iostream>
#include <algorithm>

int main()
{
    int a = 5;
    int b = 7;

    int c = std::abs(a - b);
    std::cout << "c = " << c << std::endl;
}
