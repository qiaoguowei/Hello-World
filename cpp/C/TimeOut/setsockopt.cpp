#include <iostream>

using namespace std;

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[128], recvline[129];
    struct timeval tv;

    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RECTIMEO, &tv, sizeof(tv));

    while (fgets(sendline, 128, fd) != NULL)
    {
        sendto (sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        n = recvfrom(sockfd, recvline, 128, 0, NULL, NULL);
        if (n < 0)
        {
            if (errno == EWOULDBLOCK)
            {
                cout << "socket timeout" << endl;
                continue;
            }
            else
                cout << "recvfrom error" << endl;
        }
        recvline[n] = 0;
        fputs(recvline, stdout);
    }

}
