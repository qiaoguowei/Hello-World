#include <iostream>
#include <string>
#include <openssl/bio.h>

using namespace std;

bool Base64Encode(const char *input, int inputLen, std::string& output)
{
    BIO *bmem = NULL;
    BIO *b64 = NULL;
    BUF_MEM *bptr = NULL;

    b64 = BIO_new(BIO_f_base64());
    if (!b64)
    {
        cout << "init b64 failed!" << endl;
        return false;
    }

    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

    bmem = BIO_new(BIO_s_mem());
    if (bmem)
    {
        b64 = BIO_push(b64, bmem)
        if (BIO_write(b64, input, inputLen) == inputLen)
        {
            (void)BIO_flush(b64);
            BIO_get_mem_ptr(b64, &bptr);
            ouput.clear();
            ouput.append(bptr->data(), bptr->length());
            BIO_free_all(b64);
            return true;
        }
    }
    BIO_free_all(b64);
    cout << "b64 new mem failed." << endl;
    return false;
}

bool decodeBase64(const unsigned char *inputBuf, unsigned int inputLength, 
        unsigned char **outputBuf, unsigned int &outputLength)
{
    if (!inputBuf || inputLength == 0)
    {
        cout << "decodeBase64 parameter is invalid." << endl;
        return false;
    }

    *outputBuf = new unsigned char [inputLength];
    memset(*outputBuf, 0, inputLength);

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *
}

int main(int argc, char *argv[])
{

}
