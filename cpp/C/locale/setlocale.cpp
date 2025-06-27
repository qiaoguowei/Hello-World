#include <iostream>
#include <locale.h>

int main()
{
    try
    {
        std::string cur_locale = setlocale(LC_CTYPE, "");
        std::cout << cur_locale << std::endl;

    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
