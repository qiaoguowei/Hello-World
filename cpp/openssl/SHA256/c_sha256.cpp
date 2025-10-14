#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void sha256(const unsigned char *key, unsigned int keylen, const char *input, unsigned int inputLen, char *output)
{
    unsigned char k_ipad[64] = {0};
    unsigned char k_opad[64] = {0};
    unsigned char tmp[32] = {0};

    if (keylen > 64)
    {
        SHA256(key, keylen, tmp);
        key = tmp;
        keylen = 32;
    }
    memcpy(k_ipad, key, keylen);
    memcpy(k_opad, key, keylen);

    for (int i = 0; i < 64; ++i)
    {
        k_ipad[i] ^= 0x36;
        k_opad[i] ^= 0x5c;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, k_ipad, 64);
    SHA256_Update(&sha256, input, inputLen);
    SHA256_Final(tmp, &sha256);

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, k_opad, 64);
    SHA256_Update(&sha256, tmp, 32);
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(output+(i*2), "%02x", hash[i]);
    }
}

int main()
{
    //const char *key = "c83e1177-60ba-4e50-86ed-2673164a29c5";
    //const char *input = "c83e1177-60ba-4e50-86ed-2673164a29c5-20250828";
    const char *key = "my_key";
    const char *input = "hello world";
    char output[SHA256_DIGEST_LENGTH*2 + 1] = {0};

    sha256((const unsigned char *)key, strlen(key), input, strlen(input), output);
    printf("%d\n", SHA256_DIGEST_LENGTH);
    printf("%s\n", output);
}










