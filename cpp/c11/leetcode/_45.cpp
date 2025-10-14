#include <iostream>
#include <vector>

class Solution
{
public:
    int jump(std::vector<int>& nums)
    {
        int max_pos = 0;
        int n = nums.size();
        int end = 0;
        int step = 0;

        for (int i = 0; i < n - 1; ++i)
        {
            if (max_pos >= i)
            {
                max_pos = std::max(max_pos, i + nums[i]);
                if (i == end)
                {
                    end = max_pos;
                    step++;
                }
            }
        }

        return step;
    }
};

int main()
{
    std::vector<int> nums = {2, 3, 1, 1, 4};
    Solution s;
    std::cout << s.jump(nums) << std::endl;
}
