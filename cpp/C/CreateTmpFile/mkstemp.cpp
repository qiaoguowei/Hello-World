#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>

using namespace std;

/*
 * mkstemp()函数生成一个唯一文件名并打开该文件，返回一个可用于 I/O 调用的文件描述符。
 * int mkstemp(char *template);
 * 模板参数采用路径名形式，其中最后 6 个字符必须为 XXXXXX
 * 这 6 个字符将被替换，以保证文件名的唯一性，且修改后的字符串将通过 template 参数传回
 * 因为会对传入的 template参数进行修改，所以必须将其指定为字符数组，而非字符串常量。
 * creates and opens the file, and returns an open file descriptor for the file.
 *
 * */

int main()
{
    char tempFile[1024] = {0};
    strncpy(tempFile, "unknownSubNameXXXXXX", sizeof(tempFile));
    cout << ::mkstemp(tempFile) << endl;
    cout << tempFile << endl;
}
