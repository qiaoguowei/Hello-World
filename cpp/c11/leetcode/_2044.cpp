#include <iostream>
#include <vector>

class Solution
{
public:
    int countMaxOrSubsets(const std::vector<int>& nums)
    {
        this->nums = nums;
        this->maxOr = 0;
        this->cnt = 0;
        dfs(0, 0);
        return cnt;
    }

    void dfs(int pos, int orVal)
    {
        if (pos == nums.size())
        {
            if (orVal > maxOr)
            {
                maxOr = orVal;
                cnt = 1;
            }
            else if (orVal == maxOr)
            {
                cnt++;
            }
            return ;
        }
        dfs(pos + 1, orVal | nums[pos]);
        dfs(pos + 1, orVal);
    }

private:
    std::vector<int> nums;
    int maxOr, cnt;
};

class Solution2
{
public:
    int countMaxOrSubsets(const std::vector<int>& nums)
    {
        int n = nums.size();
        int maxValue = 0;
        int cnt = 0;
        int stateNumber = 1 << n;

        for (int i = 1; i < stateNumber; i++)
        {
            int cur = 0;
            for (int j = 0; j < n; j++)
            {
                if (((i >> j) & 1) == 1)
                {
                    cur |= nums[j];
                }
            }
            if (cur == maxValue)
            {
                cnt++;
            }
            else if (cur > maxValue)
            {
                maxValue = cur;
                cnt = 1;
            }
        }

        return cnt;
    }
};

int main()
{
    Solution s;
    std::cout << s.countMaxOrSubsets({3, 1}) << std::endl;
    std::cout << s.countMaxOrSubsets({2, 2, 2}) << std::endl;
    std::cout << s.countMaxOrSubsets({3, 2, 1, 5}) << std::endl;

    Solution2 s2;
    std::cout << s2.countMaxOrSubsets({3, 1}) << std::endl;
    std::cout << s2.countMaxOrSubsets({2, 2, 2}) << std::endl;
    std::cout << s2.countMaxOrSubsets({3, 2, 1, 5}) << std::endl;
}
