#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str1 = "abcdef";

    if (str1.compare("abcdefxxx") == 0)
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }
}
