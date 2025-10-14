#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target)
    {
        std::vector<int> result(2, -1);

        int left = 0;
        int right = nums.size();
        int mid = (left + right) / 2;

        while (left < right)
        {
            if (nums[mid]== target)
            {
                for (int i = mid; i >= left; --i)
                {
                    if (nums[i] != target)
                        break;
                    result[0] = i;
                }
                for (int i = mid; i <= right; ++i)
                {
                    if (nums[i] != target)
                        break;
                    result[1] = i;
                }
                break;
            }
            else if (nums[mid] > target)
            {
                right = mid - 1;
                mid = (left + right) / 2;
            }
            else if (nums[mid] < target)
            {
                left = mid + 1;
                mid = (left + right) / 2;
            }
        }
        return result;
    }
};

int main()
{
    std::vector<int> nums = {5, 7, 7, 8, 8, 10};
    Solution s;
    std::vector<int> result = s.searchRange(nums, 8);
    std::cout << "[" << result[0] << ", " << result[1] << "]" << std::endl;

    std::vector<int> result2 = s.searchRange(nums, 6);
    std::cout << "[" << result2[0] << ", " << result2[1] << "]" << std::endl;

    std::vector<int> result3 = s.searchRange(nums, 7);
    std::cout << "[" << result3[0] << ", " << result3[1] << "]" << std::endl;
}











