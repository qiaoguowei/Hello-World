#include <iostream>
#include <string>
#include <map>
#include <functional>

using namespace std;

int main()
{
    map<time_t, string, std::greater<time_t>> mm;
    //map<time_t, string> mm;
    mm.insert(make_pair(2, "bbb"));
    mm.insert(make_pair(4, "ddd"));
    mm.insert(make_pair(1, "aaa"));
    mm.insert(make_pair(3, "ccc"));
    mm.insert(make_pair(2, "eee"));
#if 0
    auto it = mm.begin();
    for (int i = 0; i < mm.size()-1; i++)
        it++;
    mm.erase(it);
#endif
    for (auto &x : mm)
    {
        cout << x.first << ", " << x.second << endl;
    }
}
