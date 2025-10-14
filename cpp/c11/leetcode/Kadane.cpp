#include <iostream>
#include <vector>

/* Kadanes算法解决最大子数组和问题 */

int maxSubArray(const std::vector<int>& nums, std::vector<int>& max_sub_array)
{
    int current_max = nums[0];
    int total_max = nums[0];
    max_sub_array.push_back(nums[0]);
    std::vector<int> tmp_array;
    tmp_array.push_back(nums[0]);

    for (int i = 1; i < nums.size(); ++i)
    {
#if 0
        current_max = std::max(current_max + nums[i], nums[i]);
        total_max = std::max(total_max, current_max);
#else
        if (current_max + nums[i] > nums[i])
        {
            current_max = current_max + nums[i];
            tmp_array.push_back(nums[i]);
        }
        else
        {
            current_max = nums[i];
            tmp_array.clear();
            tmp_array.push_back(nums[i]);
        }

        if (total_max < current_max)
        {
            total_max = current_max;
            max_sub_array = tmp_array;
        }
#endif
    }

    return total_max;
}

int main()
{
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::vector<int> max_sub_array;
    int result = maxSubArray(nums, max_sub_array);
    std::cout << result << std::endl;
    for (auto& element : max_sub_array)
    {
        std::cout << element << ", ";
    }
    std::cout << std::endl;
}
