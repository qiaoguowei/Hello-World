#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    ostringstream oss;
    oss << "11111";
    cout << oss.str() << endl;

    oss.clear();
    oss << "22222";
    cout << oss.str() << endl;

    oss.clear();
    oss << "33333";
    cout << oss.str() << endl;

    string ss;
    ss = "11111";
    cout << ss << endl;

    ss.clear();
    ss = "22222";
    cout << ss << endl;

    ss.clear();
    ss = "33333";
    cout << ss << endl;
}
