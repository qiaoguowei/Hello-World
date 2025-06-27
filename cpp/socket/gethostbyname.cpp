#include <iostream>
#include <arpa/inet.h>
#include <string>
#include <netdb.h>
#include <cstring>

using namespace std;

int main()
{
    struct hostent *mHostStruct;
    char str[30];
    mHostStruct = ::gethostbyname("unpbook.com");
    if (mHostStruct == nullptr)
    {
        cout << "error." << hstrerror(h_errno) << endl;
        return -1;
    }

    cout << mHostStruct->h_name << endl;
    for (int i = 0; ; ++i)
    {
        if (mHostStruct->h_aliases[i] == NULL)
            break;
        cout << mHostStruct->h_aliases[i] << endl;
    }

    cout << mHostStruct->h_addrtype << endl;
    cout << mHostStruct->h_length << endl;
    for (int i = 0; ; ++i)
    {
        if (mHostStruct->h_addr_list[i] == NULL)
            break;
        bzero(str, sizeof(str));
        inet_ntop(mHostStruct->h_addrtype, mHostStruct->h_addr_list[i], str, sizeof(str));
        cout << str << endl;
    }

}
