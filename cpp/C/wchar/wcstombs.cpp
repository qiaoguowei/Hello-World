#include <iostream>
#include <cstdlib>

int main()
{
    std::wstring sToMatch = L"qiaoqiaoqiao";
    std::string sResult;
    int iLen = wcstombs(NULL, sToMatch.c_str(), 0);
    if (iLen > 0)
    {
        char *lpsz = new char[iLen + 1];
        wcstombs(lpsz, sToMatch.c_str(), iLen);
        lpsz[iLen] = '\0';
        sResult.assign(lpsz);
        delete [] lpsz;
    }
    else
    {
        sResult = "";
    }

    std::cout << sResult << std::endl;
}
