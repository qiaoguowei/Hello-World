#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
 * istream& getline (istream&  is, string& str, char delim);
 * istream& getline (istream&& is, string& str, char delim);
 * istream& getline (istream&  is, string& str);
 * istream& getline (istream&& is, string& str);
 * 默认读到换行符结束，或者delim指定的字符
 * */

int main()
{
    std::ifstream fin("./find.cpp", std::ios_base::in | std::ios_base::binary);
    std::string doc;
    std::getline(fin, doc, (char)EOF); //读整个文件
    cout << doc << endl;
}
