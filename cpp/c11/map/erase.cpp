#include <iostream>
#include <string>
#include <map>

int main()
{
    std::map<int, std::string> mm;
    mm.insert(std::make_pair(1, std::string("aaa")));
    mm.insert(std::make_pair(2, std::string("bbb")));
    mm.insert(std::make_pair(3, std::string("ccc")));

    for (auto it = mm.begin(); it != mm.end();)
    {
        if (it->first == 3 || it->first == 1 || it->first == 2)
        {
            it = mm.erase(it);
            continue;
        }

        std::cout << "111111111111" << std::endl;
        it++;
    }

    for (auto &x : mm)
    {
        std::cout << x.first << ", " << x.second << std::endl;
    }
}
