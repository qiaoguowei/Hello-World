#include <wchar.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
//#include <bits/stdc++.h>

int main()
{
    const char *str = "abcdefghijklmn";
    mbstate_t state;
    memset(&state, 0, sizeof(state));
    size_t length = mbsrtowcs(0, &str, 0, &state);
    std::cout << "strlen(str) = " << strlen(str) << std::endl;
    std::cout << "length = " << length << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    std::cout << "sizeof(wchar_t) = " << sizeof(wchar_t) << std::endl;
    wchar_t * stringBuffer = static_cast<wchar_t*>(malloc(sizeof(wchar_t)*length + 4));
    memset(&state, 0, sizeof(state));
    mbsrtowcs(stringBuffer, &str, length + 1, &state);
    std::cout << stringBuffer << std::endl;
    std::wcout << stringBuffer << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    const wchar_t *src = (const wchar_t*)stringBuffer;
    memset(&state, 0, sizeof(state));
    size_t lengthRequired = wcsrtombs(0, &src, 0, &state);
    std::cout << "lengthRequired = " << lengthRequired << std::endl;

    char *convertedStringBuffer = nullptr;
    //convertedStringBuffer = static_cast<char*>(malloc(lengthRequired + 1));
    convertedStringBuffer = new char[lengthRequired + 1];
    memset(&state, 0, sizeof(state));
    wcsrtombs(convertedStringBuffer, &src, lengthRequired + 1, &state);
    std::cout << "convertedStringBuffer = " << convertedStringBuffer << std::endl;

    free(stringBuffer);
    //free(convertedStringBuffer);
    delete[] convertedStringBuffer;
}
