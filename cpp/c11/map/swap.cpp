#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    std::map<int, string> mm;
    mm.insert(make_pair(1, "aaa"));
    mm.insert(make_pair(2, "ddd"));
    mm.insert(make_pair(3, "ccc"));

    std::map<int, string> mm2;
    mm2.swap(mm);

    cout << mm.size() << endl;
    cout << mm2.size() << endl;
}
