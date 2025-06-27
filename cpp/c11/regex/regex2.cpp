#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main()
{
    string data = "XML tag: <tag-name>the value</tag-name>.";
    cout << "data:    " << data << "\n\n";

    smatch m;
    bool found = regex_search(data, m, regex("<(.*)>(.*)</(\\1)>"));

    cout << "m.empty() : " << boolalpha << m.empty() << endl;
    cout << "m.size() :  " << m.size() << endl;
    if (found)
    {
        cout << "m.str() :      " << m.str() << endl;
        cout << "m.length() :   " << m.length() << endl;
        cout << "m.position() : " << m.position() << endl;
        cout << "m.prefix() :   " << m.prefix() << endl;
        cout << "m.suffix() :   " << m.suffix() << endl;

        for (int i = 0; i < m.size(); i++)
        {
            cout << "m[" << i << "].str():    " << m[i].str() << endl;
            cout << "m.str(" << i << "):      " << m.str(i) << endl;
            cout << "m.position(" << i << "): " << m.position(i) << endl;
        }

        cout << "matches: " << endl;
        for (auto pos = m.begin(); pos != m.end(); pos++)
        {
            cout << " " << *pos << " " << endl;
            cout << "(length: " << pos->length() << ")" << endl;
        }
    }
}
