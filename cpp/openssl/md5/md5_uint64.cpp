#include <iostream>
#include <string>
#include <openssl/md5.h>

using namespace std;

int main()
{
    string str1 = "asdflkjsadoislejgrejgoiajijjlkdjg";
    uint64_t digests[MD5_DIGEST_LENGTH / 8];
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, str1.c_str(), str1.size());
    MD5_Final((unsigned char *)digests, &ctx);

    cout << digests[0] << endl;
    cout << digests[1] << endl;
}
