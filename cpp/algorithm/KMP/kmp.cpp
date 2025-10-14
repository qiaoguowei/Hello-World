#include <iostream>
#include <vector>

//abcac
//[0, 0, 0, 1, 0]
void build_next(const std::vector<char>& p, std::vector<int>& next)
{
    size_t m = p.size();
    next.reserve(m);
    next.assign(m, 0);
    int j = 0;

    for (int i = 1; i < m; ++i)
    {
        while (j > 0 && p[i] != p[j])
        {
            j = next[j - 1];
        }
        if (p[i] == p[j])
        {
            j += 1;
        }
        next[i] = j;
    }
}

void kmp_search(const std::vector<char>& text, const std::vector<char>& pattern, std::vector<int>& result)
{
    size_t n = text.size();
    size_t m = pattern.size();

    std::vector<int> next;
    build_next(pattern, next);
    int j = 0;

    for (int i = 0; i < n; ++i)
    {
        while (j > 0 && text[i] != pattern[j])
        {
            j = next[j - 1];
        }
        if (text[i] == pattern[j])
            j += 1;
        if (j == m)
        {
            result.push_back(i - m + 1);
            j = next[j - 1];
        }
    }
}

int main()
{
    std::vector<char> text = {'a', 'b', 'a', 'b', 'c', 'a', 'b', 'c', 'a', 'c', 'b', 'a', 'b'};
    std::vector<char> pattern = {'a', 'b', 'c', 'a', 'c'};
    std::vector<int> result;

    kmp_search(text, pattern, result);
    for (auto& x : result)
    {
        std::cout << x << std::endl;
    }
}

















