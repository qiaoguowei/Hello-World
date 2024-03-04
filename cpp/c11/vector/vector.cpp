#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string> vv;

    string str1 = "aaaa";
    vv.push_back(str1);
    cout << &str1 << endl;
    cout << vv.at(0) << endl;
}
