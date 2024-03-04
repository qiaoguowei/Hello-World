#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    std::vector<int> nums = {1, 5, 4};

    for (auto& x : nums)
    {
        cout << x << ", ";
    }
    cout << endl;

    std::sort(nums.begin(), nums.end());

    for (auto& x : nums)
    {
        cout << x << ", ";
    }
    cout << endl;
}
