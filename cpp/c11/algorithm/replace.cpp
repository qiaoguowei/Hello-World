#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    //string old_str = "\"LIUXIAOYUN\".\"3万数据.csv\"";
    string old_str = "`LIUXIAOYUN`.`3万数据.csv`";

    replace(old_str.begin(), old_str.end(), '\"', '`');
    cout << old_str << endl;
}
