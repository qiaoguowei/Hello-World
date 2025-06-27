#include <wchar.h>
#include <iostream>
#include <cstring>
//#include <bits/stdc++.h>

int main()
{
    const char *str = "abcdefghijklmn";
    mbstate_t state;
    memset(&state, 0, sizeof(state));
    size_t length = mbsrtowcs(0, &str, 0, &state);
    std::cout << "strlen(str) = " << strlen(str) << std::endl;
    std::cout << "length = " << length << std::endl;

    wchar_t * stringBuffer = static_cast<wchar_t*>(malloc(length + 1));
    memset(&state, 0, sizeof(state));
    mbsrtowcs(stringBuffer, &str, length + 1, &state);
    std::cout << stringBuffer << std::endl;
    std::wcout << stringBuffer << std::endl;
    free(stringBuffer);
}
