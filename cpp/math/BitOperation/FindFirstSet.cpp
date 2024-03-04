#include <iostream>

using namespace std;

template <typename T>
inline int findFirstSet(T mask)
{
    if (!mask)
        return 0;
    int index = 1;
    T t = 1;
    while ((mask & t) == 0)
    {
        t = t << 1;
        ++index;
    }
    return index;
}

/*
 * __builtin_ffs 是 gcc 内置的函数，获取一个数值：从低位起，第一个1 出现的位置，如0x11，返回的是1,0x00返回的是0,0x02，返回的是2
 * */

int main()
{
    int a = 0x10;
    long b = 2;
    int16_t c = 4;

    cout << findFirstSet(a) << endl;
    cout << findFirstSet(b) << endl;
    cout << findFirstSet(c) << endl;
#if defined(__GNUC__)
    cout << __builtin_ffs(a) << endl;
    cout << __builtin_ffsll(b) << endl;
#endif
}
