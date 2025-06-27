#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> nums = {1, 2, 3, 4, 5};

    for (int x : nums)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    int i = 0;
    while (std::next_permutation(nums.begin(), nums.end()))
    {
        for (int x : nums)
        {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        i++;
    }
    std::cout << "i = " << i << std::endl;
}
