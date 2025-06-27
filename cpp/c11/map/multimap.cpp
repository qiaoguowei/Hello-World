#include <iostream>
#include <string>
#include <map>
#include <functional>

using namespace std;

int main()
{
    multimap<time_t, string, std::greater<time_t>> mm;
    mm.insert(make_pair(2, "bbb"));
    mm.insert(make_pair(4, "ddd"));
    mm.insert(make_pair(1, "aaa"));
    mm.insert(make_pair(2, "ccc"));
    mm.insert(make_pair(1, "eee"));

    auto m3 = mm;
    cout << m3.size() << endl;

    cout << mm.count(2) << endl;

    auto iter = mm.find(2);
    for (iter; iter->first == 2; iter++)
    {
        cout << iter->first << ", " << iter->second << endl;
    }

    map<string, multimap<int, string>> m2;

    m2["bbb"].insert(make_pair(1, "aaa"));
    if (m2["bbb"].find(1) != m2["bbb"].end())
    {
        cout << "find success." << endl;
    }

    //for (auto &x : mm)
    //{
    //    cout << x.first << ", " << x.second << endl;
    //}
}
