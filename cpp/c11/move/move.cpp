#include <iostream>
#include <utility>
#include <vector>

int main()
{
    std::vector<int> vec;

    int a = 10;
    vec.push_back(std::move(a));

    std::cout << "vec[0] = " << vec[0] << std::endl;
    std::cout << "a = " << a << std::endl;
    vec[0] = 11;
    std::cout << "vec[0] = " << vec[0] << std::endl;
    std::cout << "a = " << a << std::endl;
}
