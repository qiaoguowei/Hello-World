#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char *argv[])
{
    char *ptr;
    char **pptr;
    char str[INET_ADDRSTRLEN];
    struct hostent *hptr;

    while (--argc > 0)
    {
        ptr = *++argv;
        if ((hptr = gethostbyname(ptr)) == NULL)
        {
            cout << "gethostbyname error for host: " << ptr << " :" << hstrerror(h_errno) << endl;
            continue;
        }

        cout << "official hostname: " << hptr->h_name << endl;

        for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
        {
            cout << "\talias: " << *pptr << endl;
        }

        switch (hptr->h_addrtype)
        {
            case AF_INET:
                pptr = hptr->h_addr_list;
                for ( ; *pptr != NULL; pptr++)
                {
                    cout << "\taddress: " << inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)) << endl;
                }
                break;
            default:
                cout << "unknown address type." << endl;
                break;
        }
    }
}
