#include <iostream>

using namespace std;

/*
 * __builtin_popcount = int
 * __builtin_popcountl = long int
 * __builtin_popcountll = long long
 *
 * 这个函数功能：返回输入数据中，二进制中‘1’的个数。
 *
 * */

int main()
{
    int a = 1 + (1 << 5) + (1 << 3);

    cout << __builtin_popcount(a) << endl;
    cout << a << endl;
}
