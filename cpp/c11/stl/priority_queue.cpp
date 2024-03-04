#include <iostream>
#include <queue>

template <typename T>
class CompirePriority
{
public:
    bool operator() (std::pair<int, T> a, std::pair<int, T> b)
    {
        return a.first > b.first;
    }
};

int main()
{
    std::priority_queue<std::string, std::vector<std::pair<int, std::string>>, CompirePriority<std::string>> m_queue;
}
