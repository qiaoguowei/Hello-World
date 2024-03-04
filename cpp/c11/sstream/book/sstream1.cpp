#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;

int main()
{
    ostringstream os;

    os << "dec: " << 15 << hex << " hex: " << 15 << endl;
    cout << os.str() << endl;

    bitset<15> b(5678);
    os << "float: " << 4.67 << " bitset: " << b << endl;
    os.seekp(0);
    os << "oct: " << oct << 15;
    cout << os.str() << endl;
}

/*
 * 首先是一个十进制数和一个十六进制数写至 os，接下来增加一个浮点数和一个bitset。
 * 然后运用seekp（）将涂写位置设于stream起始处，这么一来后继的operator＜＜就把输出写到string头部，
 * 于是覆盖了原本的string stream头部内容。未被覆盖的字符依然有效。如果你要删除stream的现有内容，
 * 可利用函数str（）将崭新内容赋予缓冲区：strm.str("");
 * */
