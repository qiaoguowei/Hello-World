#include <iostream>
#include <stdlib.h>

using namespace std;

/*
 * tmpfile()函数会创建一个名称唯一的临时文件，并以读写方式将其打开。
 * （打开该文件时使用了 O_EXCL 标志，以防一个可能性极小的冲突，即另一个进程已经创建了一个同名文件。）
 * FILE *tmpfile(void);
 *
 * tmpfile()函数执行成功，将返回一个文件流供 stdio 库函数使用。
 * 文件流关闭后将自动删除临时文件。
 * 为达到这一目的，tmpfile()函数会在关闭文件后，从内部立即调用 unlink()来删除该文件名
 *
 * */

int main()
{

}
