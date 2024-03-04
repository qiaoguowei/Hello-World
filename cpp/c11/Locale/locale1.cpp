#include <iostream>
#include <locale>
#include <string>

using namespace std;

int main()
{
    try
    {
        locale langLocale("");
        //create the default locale from the user's environment

        cout.imbue(langLocale);

        cout << langLocale.name() << endl;
    }
    catch (std::exception& e)
    {
        cerr << e.what() << endl;
    }
}
