#include <iostream>
#include <cstdlib>

int main()
{
    std::string sToMatch = "qiaoqiaoqiao";
    std::wstring wsToMatch;

    int iWlen = mbstowcs(NULL, sToMatch.c_str(), sToMatch.length());
    wchar_t *lpwsz = new wchar_t[iWlen + 1];
    mbstowcs(lpwsz, sToMatch.c_str(), sToMatch.length());
    wsToMatch.assign(lpwsz);
    delete [] lpwsz;

    std::wcout << wsToMatch << std::endl;
}
