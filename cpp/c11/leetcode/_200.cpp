#include <iostream>
#include <vector>

class Solution
{
public:
    void dfs(std::vector<std::vector<char>>& grid, int r, int c)
    {
        int nr = grid.size();
        int nc = grid[0].size();

        grid[r][c] = '0';
        if (r - 1 >= 0 && grid[r - 1][c] == '1')
            dfs(grid, r - 1, c);
        if (r + 1 < nr && grid[r + 1][c] == '1')
            dfs(grid, r + 1, c);
        if (c - 1 >= 0 && grid[r][c - 1] == '1')
            dfs(grid, r, c - 1);
        if (c + 1 < nc && grid[r][c + 1] == '1')
            dfs(grid, r, c + 1);
    }

public:
    int numIslands(std::vector<std::vector<char>>& grid)
    {
        int nr = grid.size();
        if (!nr)
            return 0;
        int nc = grid[0].size();

        int num_islands = 0;
        for (int r = 0; r < nr; ++r)
        {
            for (int c = 0; c < nc; ++c)
            {
                if (grid[r][c] == '1')
                {
                    ++num_islands;
                    dfs(grid, r, c);
                }
            }
        }

        return num_islands;
    }
};

int main()
{
    std::vector<std::vector<char>> grid;
    std::vector<char> sub_grid1 = {'1', '1', '1', '1', '0'};
    std::vector<char> sub_grid2 = {'1', '1', '0', '1', '0'};
    std::vector<char> sub_grid3 = {'1', '1', '0', '0', '0'};
    std::vector<char> sub_grid4 = {'0', '0', '0', '0', '0'};
    grid.push_back(sub_grid1);
    grid.push_back(sub_grid2);
    grid.push_back(sub_grid3);
    grid.push_back(sub_grid4);

    Solution s;
    std::cout << "The numbers of islands is " << s.numIslands(grid) << std::endl;

}
