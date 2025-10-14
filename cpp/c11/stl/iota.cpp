#include <iostream>
#include <vector>
#include <numeric>

int main()
{
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0); // 填充0..9

    for (int x : v)
        std::cout << x << " ";
    std::cout << std::endl;
}
