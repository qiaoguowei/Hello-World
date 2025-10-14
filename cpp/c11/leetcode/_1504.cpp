#include <iostream>
#include <vector>

class Solution
{
public:
#if 0
    int numSubmat(std::vector<std::vector<int>>& mat)
    {
        int result = 0;
        int mat_size = mat.size();
        for (int i = 0; i < mat_size; i++)
        {
            for (int j = 0; j < mat[i].size(); j++)
            {
                if (mat[i][j] == 1)
                    result += 1;
                int tmp_i = i;
                int tmp_j = j;
                int threshold_j = 0;
                for (; tmp_i >= 0; tmp_i--)
                {
                    bool is_break = false;
                    for (; tmp_j >= threshold_j; tmp_j--)
                    {
                        if (tmp_i == i && tmp_j == j)
                            continue;
                        if (mat[tmp_i][tmp_j] == 1)
                            result += 1;
                        else
                        {
                            if (tmp_i < i)
                                is_break = true;
                            threshold_j = tmp_j;
                            break;
                        }
                    }

                    if (is_break)
                        break;
                }
            }
        }

        return result;
    }
#else
    int numSubmat(std::vector<std::vector<int>>& mat)
    {
        int m = mat.size(), n = mat[0].size();
        int res = 0;
        std::vector<std::vector<int>> row(m, std::vector<int>(n, 0));

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (j == 0)
                {
                    row[i][j] = mat[i][j];
                }
                else
                {
                    row[i][j] = (mat[i][j] == 0) ? 0 : row[i][j - 1] + 1;
                }
                int cur = row[i][j];
                for (int k = i; k >= 0; --k)
                {
                    cur = std::min(cur, row[k][j]);
                    if (cur == 0)
                    {
                        break;
                    }
                    res += cur;
                }
            }
        }
        return res;

    }
#endif
};

int main()
{
    std::vector<std::vector<int>> mat;

    std::vector<int> submat1;
    submat1.push_back(1);
    submat1.push_back(0);
    submat1.push_back(1);
    mat.emplace_back(submat1);
    std::vector<int> submat2;
    submat2.push_back(1);
    submat2.push_back(1);
    submat2.push_back(0);
    mat.emplace_back(submat2);
    std::vector<int> submat3;
    submat3.push_back(1);
    submat3.push_back(1);
    submat3.push_back(0);
    mat.emplace_back(submat3);

    Solution s;
    int result = s.numSubmat(mat);
    std::cout << result << std::endl;
}
