#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs)
    {
        std::unordered_map<std::string, std::vector<std::string>> mp;
        for (const std::string& str : strs)
        {
            std::string key = str;
            std::sort(key.begin(), key.end());
            mp[key].emplace_back(str);
        }

        std::vector<std::vector<std::string>> ans;
        for (std::unordered_map<std::string, std::vector<std::string>>::iterator iter = mp.begin();
                iter != mp.end(); ++iter)
        {
            ans.emplace_back(iter->second);
        }
        return ans;
    }
};

int main()
{
    Solution s;
    std::vector<std::vector<std::string>> result = s.groupAnagrams({"eat","tea","tan","ate","nat","bat"});

    for (auto& strs : result)
    {
        for (auto& str : strs)
        {
            std::cout << str << ", ";
        }
        std::cout << std::endl;
        std::cout << "----------------------" << std::endl;
    }
}
