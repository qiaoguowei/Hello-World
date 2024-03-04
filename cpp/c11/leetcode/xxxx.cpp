#include <iostream>
#include <string>
#include <list>

using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        uint8_t m_hash[256] = {0};
        string tmp;
        std::list<pair<int, string>> res;

        for (auto x = s.begin(); x != s.end(); ++x)
        {
            if (m_hash[*x] == 1)
            {
                res.push_back(make_pair(tmp.size(), tmp));
                size_t pos = tmp.find(*x);
                if (pos != std::string::npos)
                {
                    for (int i = 0; i < pos; i++)
                    {
                        m_hash[tmp[i]] = 0;
                    }
                    tmp.erase(0, pos+1);
                }
                tmp += *x;
            }
            else
            {
                tmp += *x;
                m_hash[*x] = 1;
            }
        }
        res.push_back(make_pair(tmp.size(), tmp));
        res.sort();
        for (auto& x : res)
            cout << x.second << endl;
        return res.back().first;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    cout << s.lengthOfLongestSubstring(string(argv[1])) << endl;
}













