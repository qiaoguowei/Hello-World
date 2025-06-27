#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

/*
 * 和C的文件访问机制相比，C++file stream class的最大好处就是文件的自动管理。
 * 文件可在构造时期自动打开，析构时期自动关闭。这当然是因为定义了适当的构造函数和析构函数。
 * */

void writeCharsetToFile(const string& filename);
void outputFile(const string& filename);

int main()
{
    writeCharsetToFile("charset.out");
    outputFile("charset.out");
}

void writeCharsetToFile(const string& filename)
{
    ofstream file(filename);

    if (!file)
    {
        cerr << "can't open output file \"" << filename << "\"" << endl;
        return;
    }

    for (int i = 32; i < 256; ++i)
    {
        file << "value: " << setw(3) << i << "   "
             << "char:  " << static_cast<char>(i) << endl;
    }
} //close file automatically

void outputFile(const string& filename)
{
    ifstream file(filename);

    if (!file)
    {
        cerr << "can't open input file \"" << filename << "\"" << endl;
        return;
    }

    char c;
    while (file.get(c))
    {
        cout.put(c);
    }
} //close file automatically

















