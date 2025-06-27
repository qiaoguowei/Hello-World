#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

/*
 * 函数的作用是:返回一个指向新字符串的指针，该指针是新字符串的副本。
 * 新字符串的内存由malloc(3)获取，并可由free(3)释放。
 * char *strdup(const char *s);
 *
 * */

using namespace std;

int main()
{
    char *firstStr = static_cast<char *>(malloc(64));
    memset(firstStr, 0, 64);
    strncpy(firstStr, "this is the first point", 64);

    char *secondStr = strdup(firstStr);

    cout << firstStr << endl;
    printf("%p\n", firstStr);
    cout << secondStr << endl;
    printf("%p\n", secondStr);

    free(firstStr);
    free(secondStr);
}
