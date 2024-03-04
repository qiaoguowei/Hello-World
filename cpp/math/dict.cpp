#include <iostream>
#include <string>

//功能：将mask转化为2进制，看含有的1的个数。
//每执行一次x = x&(x-1)，会将x用二进制表示时最右边的一个1变为0，因为x-1将会将该位(x用二进制表示时最右边的一个1)变为0。
int main()
{
    uint32_t mask = 2047;
    while (mask)
    {
        std::cout  << "__builtin_ffs(mask) : " << __builtin_ffs(mask) << std::endl;
        mask &= (mask - 1);
        std::cout << mask << std::endl;
    }
}
