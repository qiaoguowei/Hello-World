#include <iostream>
#include <string>
#include <openssl/md5.h>

using namespace std;

int main()
{
<<<<<<< HEAD
    string str1 = "ZZC9ZJ3CSGExtensionMatcherEncrypt";
=======
    string str1 = "asdflkjsadoislejgrejgoiajijjlkdjg";
>>>>>>> 4adb3f20a968faa466b0157e6da162535c178879
    uint64_t digests[MD5_DIGEST_LENGTH / 8];
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, str1.c_str(), str1.size());
    MD5_Final((unsigned char *)digests, &ctx);

    cout << digests[0] << endl;
    cout << digests[1] << endl;
}
