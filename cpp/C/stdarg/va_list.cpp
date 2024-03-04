#include <iostream>
#include <stdarg.h>

using namespace std;
/*
 * void f1(int n, ...);
 * int f2(const char *s, int k, ...);
 *
 * */

double sum(int lim, ...)
{
    va_list ap;     //申明一个存储参数的对象

    //在该例中，lim是parmN形参，它表明变参列表中参数的数量
    va_start(ap, lim);  //把ap初始化为参数列表

    //下一步是访问参数列表的内容，这涉及使用另一个宏va_arg()。
    //例如，如果参数列表中的第1个参数是double类型，第2个参数是int类型，可以这样做：
    double tic;
    int toc;

    tic = va_arg(ap, double);   //检索第一个参数
    toc = va_arg(ap, int);      //检索第二个参数
    //注意，传入的参数类型必须与宏参数的类型相匹配。
    //如果第1个参数是10.0，上面tic那行代码可以正常工作。但是如果参数是10，这行代码可能会出错

    //最后，要使用va_end()宏完成清理工作。例如，释放动态分配用于存储参数的内存。
    va_end(ap);
}


int main()
{
}
