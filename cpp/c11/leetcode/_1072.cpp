#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

class Solution
{
public:
    int maxEqualRowsAfterFlips(std::vector<std::vector<int>>& matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        std::unordered_map<std::string, int> mp;

        for (int i = 0; i < m; i++)
        {
            std::string s = std::string(n, '0');
            for (int j = 0; j < n; j++)
            {
                //如果matrix[i][0]为1，则对该元素进行翻转
                s[j] = '0' + (matrix[i][j] ^ matrix[i][0]);
            }
            mp[s]++;
        }

        int res = 0;
        for (auto& m_pair : mp)
        {
            res = std::max(res, m_pair.second);
            std::cout << m_pair.first << std::endl;
        }
        return res;
    }
};

int main()
{
    std::vector<std::vector<int>> matrix = {{0, 0, 0}, {0, 0, 1}, {1, 1, 0}};
    Solution s;
    int res = s.maxEqualRowsAfterFlips(matrix);
    std::cout << res << std::endl;
}


