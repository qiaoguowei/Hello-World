#include <iostream>
#include <cstring>
#include <openssl/md5.h>

using namespace std;
//unsigned char *MD5(const unsigned char *d, size_t n, unsigned char *md);
uint64_t Mhash(const unsigned char *data, size_t length)
{
    if (!data || !length)
    {
        cout << "data pointer or length is 0." << endl;
        return 0;
    }
#if 1
    uint64_t digests[MD5_DIGEST_LENGTH / 8];
    MD5(data, length, (unsigned char *)digests);
    for (auto x : digests)
    {
        cout << x << " ";
    }
    cout << endl;
#else
    unsigned char buf[MD5_DIGEST_LENGTH + 1];
    memset(buf, 0, sizeof(buf));
    MD5(data, length, buf);
    cout << buf << endl;
#endif
    return digests[0];
    //return 1;
}

int main()
{
    unsigned char buf[] = "ZZC9ZJ3CSGExtensionMatcherEncrypt";
    cout << Mhash(buf, (size_t)strlen((char *)buf)) << endl;
}
