#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <climits>

class PairHash
{
public:
    size_t operator()(const std::pair<int, int>& m_pair) const
    {
        return std::hash<int>()(m_pair.first) ^ std::hash<int>()(m_pair.second);
    }
};

int main()
{
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    std::vector<std::string> position(n);
    std::pair<int, int> s_position;
    std::pair<int, int> e_position;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> position[i];
        for (int j = 0; j < m; ++j)
        {
            if (position[i][j] == 'S')
                s_position = std::make_pair(i, j);
            else if (position[i][j] == 'E')
                e_position = std::make_pair(i, j);
        }
    }

    std::unordered_set<std::pair<int, int>, PairHash> distinct;
    std::queue<std::pair<int, int>> q;
    q.push(s_position);
    distinct.insert(s_position);

    std::vector<std::vector<int>> e_position_range(2, std::vector<int>({e_position.first, e_position.second}));
    std::queue<std::pair<int, int>> qe;
    std::unordered_set<std::pair<int, int>, PairHash> distinct_end;
    qe.push(e_position);
    distinct_end.insert(e_position);
    while (!qe.empty())
    {
        auto& [x, y] = qe.front();
        qe.pop();
        if (x > 0 && position[x - 1][y] == '.' && !distinct_end.count(std::make_pair(x - 1, y)))
        {
            qe.push(std::make_pair(x - 1, y));
            distinct_end.insert(std::make_pair(x - 1, y));
            e_position_range[0][0] = std::min(e_position_range[0][0], x - 1);
        }
        if (x < n - 1 && position[x + 1][y] == '.' && !distinct_end.count(std::make_pair(x + 1, y)))
        {
            qe.push(std::make_pair(x + 1, y));
            distinct_end.insert(std::make_pair(x + 1, y));
            e_position_range[0][1] = std::max(e_position_range[0][1], x + 1);
        }
        if (y > 0 && position[x][y - 1] == '.' && !distinct_end.count(std::make_pair(x, y - 1)))
        {
            qe.push(std::make_pair(x, y - 1));
            distinct_end.insert(std::make_pair(x, y - 1));
            e_position_range[1][0] = std::min(e_position_range[1][0], y - 1);
        }
        if (y < m - 1 && position[x][y + 1] == '.' && !distinct_end.count(std::make_pair(x, y + 1)))
        {
            qe.push(std::make_pair(x, y + 1));
            distinct_end.insert(std::make_pair(x, y + 1));
            e_position_range[1][1] = std::max(e_position_range[1][1], y + 1);
        }
    }
    std::cout << e_position_range[0][0] << ",";
    std::cout << e_position_range[0][1] << ",";
    std::cout << e_position_range[1][0] << ",";
    std::cout << e_position_range[1][1] << std::endl;

    while (!q.empty())
    {
        auto& [x, y] = q.front();
        q.pop();
        if ((x - 1 <= e_position_range[0][1] && x - 1 >= e_position_range[0][0]) ||
            (x + 1 <= e_position_range[0][1] && x + 1 >= e_position_range[0][0]) ||
            (x <= e_position_range[0][1] && x >= e_position_range[0][0]) ||
            (y - 1 <= e_position_range[1][1] && y - 1 >= e_position_range[1][0]) ||
            (y + 1 <= e_position_range[1][1] && y + 1 >= e_position_range[1][0]) ||
            (y <= e_position_range[1][1] && y >= e_position_range[1][0]))
        {
            std::cout << "YES" << std::endl;
            return 0;
        }

        if (x > 0 && position[x - 1][y] == '.' && !distinct.count(std::make_pair(x - 1, y)))
        {
            q.push(std::make_pair(x - 1, y));
            distinct.insert(std::make_pair(x - 1, y));
        }
        if (x < n - 1 && position[x + 1][y] == '.' && !distinct.count(std::make_pair(x + 1, y)))
        {
            q.push(std::make_pair(x + 1, y));
            distinct.insert(std::make_pair(x + 1, y));
        }
        if (y > 0 && position[x][y - 1] == '.' && !distinct.count(std::make_pair(x, y - 1)))
        {
            q.push(std::make_pair(x, y - 1));
            distinct.insert(std::make_pair(x, y - 1));
        }
        if (y < m - 1 && position[x][y + 1] == '.' && !distinct.count(std::make_pair(x, y + 1)))
        {
            q.push(std::make_pair(x, y + 1));
            distinct.insert(std::make_pair(x, y + 1));
        }
    }

    std::cout << "NO" << std::endl;
    return 0;
}




