#include <iostream>
#include <unordered_map>

int main()
{
    std::unordered_map<std::string, int> words;
    std::string w = "aaa";
    if (!words.count(w))
        words[w] += 1;

    for (auto& x : words)
    {
        std::cout << x.first << ", " << x.second;
    }
    std::cout << std::endl;
}
