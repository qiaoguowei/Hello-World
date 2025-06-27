#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(std::vector<int>& vt)
{
    for (auto &x : vt)
    {
        cout << x << " ";
    }
    cout << endl;
}

int main()
{
    std::vector<int> vt = {4, 5, 6, 2, 5, 7, 8, 9, 4, 3};
    print(vt);

    std::sort(vt.begin(), vt.end());
    print(vt);

    auto iter = std::unique(vt.begin(), vt.end());
    print(vt);

    vt.erase(iter, vt.end());
    print(vt);
}
