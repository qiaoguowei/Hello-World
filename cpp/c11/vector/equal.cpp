#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> vec1({5, 4, 3, 2, 1});
    std::vector<int> vec2({1, 2, 3, 4, 5});

    std::sort(vec1.begin(), vec1.end());
    std::sort(vec2.begin(), vec2.end());

    if (std::equal(vec1.begin(), vec1.end(), vec2.begin()))
    {
        std::cout << "equal" << std::endl;
    }
}
