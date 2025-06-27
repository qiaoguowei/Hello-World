#include <iostream>
#include <vector>

class Solution
{
public:
    long long totalCost(std::vector<int>& costs, int k, int candidates)
    {
        long long total = 0;
        while (k--)
        {
            int min = 1000000;
            int index = 0;
            for (int i = 0; i < (candidates > costs.size() ? costs.size() : candidates); i++)
            {
                if (min > costs[i])
                {
                    min = costs[i];
                    index = i;
                }
            }

            for (int j = (costs.size() < candidates ? 0 : costs.size() - candidates); j < costs.size(); j++)
            {
                if (min > costs[j])
                {
                    min = costs[j];
                    index = j;
                }
            }
            costs.erase(costs.begin()+index);
            std::cout << "min: " << min << std::endl;
            for (auto& x : costs)
                std::cout << x << " ";
            std::cout << std::endl;
            total += min;
        }
        return total;
    }
};

int main()
{
    //std::vector<int> costs = {17, 12, 10, 2, 7, 2, 11, 20, 8};
    std::vector<int> costs = {17, 12, 10, 2, 7};
    int k = 3;
    int candidates = 4;
    Solution s;
    long long total = s.totalCost(costs, k, candidates);
    std::cout << total << std::endl;
}
