#include <iostream>
#include <cstring>

using namespace std;

int main()
{
#if 0
    char Array[2000] = {'0'};
    char *p = Array;
    cout << strlen(p) << endl;
#endif
    std::string a = "多类型文件/多层/大量目录及文件/超长文件名8888888888888888888888888888888文件指纹/Excel/Master document to rule them all/Master Excel/Word from Excel (copy-paste)-send/Word from Excel (copy-paste) - save as Encoded Text - Western European (DOS).txt";

    std::cout << a << std::endl;
    std::cout << a.size() << std::endl;
}
