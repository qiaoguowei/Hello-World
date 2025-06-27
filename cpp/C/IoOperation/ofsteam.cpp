#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;
int main()
{
    umask(0022);
    ofstream fout("./001", ofstream::out | ofstream::binary);

    fout << "123456" << endl;
    fout.close();
}
