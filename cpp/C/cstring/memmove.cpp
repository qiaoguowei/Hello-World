#include <iostream>
#include <cstring>

/*
    void *memmove(void *dest, const void *src, size_t n);

    memmove()函数将n个字节从内存区域src复制到内存区域dest。
    内存区域可能重叠:复制发生时，好像src中的字节首先被复制到一个不与src或dest重叠的临时数组中，然后这些字节从临时数组复制到dest。

RETURN VALUE
    The memmove() function returns a pointer to dest.
 */

int main()
{
    char s[]="Golden Global View";
    std::cout << s << std::endl;

    //memmove(s, s + 7, strlen(s) + 1 - 7);
    memmove(s, s + 7, strlen(s) - 7);
    std::cout << s << std::endl;
}
