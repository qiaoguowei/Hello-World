#include <iostream>
#include <stdio.h>

using namespace std;

/*
 * int rename(const char *oldname, const char *newname);
 * oldname指向      newname所示文件不存在       newname指向普通文件     newname指向目录文件
 * 普通文件         文件成功重命名              newname被删除，oldname  错误
 *                                              重命名为newname
 *
 * 目录文件         文件成功重命名              错误                    若该目录为空目录则被删除
 *                                                                      oldname被重命名，否则出错
 *
 * 对于重命名目录文件的情况，有一点需要注意的，newname不能包含有oldname的路径前缀，也就是说，不能将一个目录文件重命名为它的子文件。
 * */

int main()
{
}
