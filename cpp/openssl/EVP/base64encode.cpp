#include <iostream>
#include <string>
#include <cstring>
#include <openssl/evp.h>

using namespace std;

int main()
{
	EVP_ENCODE_CTX *ectx;
	unsigned char in[500], out[800], d[500];
	int in1, out1, total, ret, total2;
	int i;

	ectx = EVP_ENCODE_CTX_new();
	EVP_EncodeInit(ectx);
	for (i = 0; i < 500; ++i)
	{
		memset(&in[i], i, 1);
	}
	in1 = 500;
	total = 0;
	EVP_EncodeUpdate(ectx, out, &out1, in, in1);
	total += out1;
	EVP_EncodeFinal(ectx, out + total, &out1);
	total += out1;

	cout << out << endl;

	EVP_ENCODE_CTX_free(ectx);
}
