#include <iostream>
#include <string>
#include <openssl/rsa.h>

using namespace std;

int main()
{
    RSA *r;
    int bits = 512;
    int ret;
    unsigned long e = RSA_3;
    BIGNUM *bne;

    //r = RSA_generate_key(bits, e, NULL, NULL);
    //RSA_print_fp(stdout, r, 11);
    //RSA_free(r);
    bne = BN_new();
    ret = BN_set_word(bne, e);
    r = RSA_new();
    ret = RSA_generate_key_ex(r, bits, bne, NULL);
    if (ret != 1)
    {
        cout << "RSA_generate_key_ex!" << endl;
        return -1;
    }
    RSA_print_fp(stdout, r, 11);

    RSA_free(r);
    return 0;
}
/*
 * 调用 RSA_generate_key 和 RSA_generate_key_ex 函数生成 RSA 密钥
 * 调用 RSA_print_fp 打印密钥信息
 * */
