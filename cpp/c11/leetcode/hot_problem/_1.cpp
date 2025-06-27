#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    static std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        std::unordered_map<int, int> hashtable;

        for (int i = 0; i < nums.size(); ++i)
        {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end())
            {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }

        return {};
    }
};


int main()
{
    std::vector<int> nums = {2,7,11,15};
    std::vector<int> result = Solution::twoSum(nums, 9);
    for (auto& x : result)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}
