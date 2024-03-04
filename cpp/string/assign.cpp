#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main()
{
    char buf[9] = {0};
    snprintf(buf, sizeof(buf), "123456789");
    string str;
    str.assign(buf);
    cout << str << endl;
    cout << str.size() << endl;
}
