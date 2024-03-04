#include <iostream>
#include <map>

int main()
{
    std::map<int, std::string> mm =
    {
        {1, std::string("aaaaa")},
        {2, std::string("bbbbb")},
        {3, std::string("ccccc")},
        {4, std::string("ddddd")},
        {5, std::string("eeeee")}
    };

    while (mm.size() > 3)
    {
        std::map<int, std::string>::iterator iter = mm.begin();
        std::cout << "delete : {" << iter->first << ", " << iter->second << "}" << std::endl;
        mm.erase(iter);
    }

    for (auto& x : mm)
    {
        std::cout << "{ " << x.first << ", " << x.second << " }" << std::endl;
    }
}
