#include <iostream>
#include <wchar.h>

int main()
{
    const wchar_t *wstr1 = L"abcd";
    const wchar_t *wstr2 = L"abcd";
    const wchar_t *wstr3 = L"aaaa";

    int result = wcscmp(wstr1, wstr2);
    std::cout << "result = " << result << std::endl;

    int result2 = wcscmp(wstr1, wstr3);
    std::cout << "result2 = " << result2 << std::endl;

    int result3 = wcscmp(wstr3, wstr1);
    std::cout << "result3 = " << result3 << std::endl;
}
