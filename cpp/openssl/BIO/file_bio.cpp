#include <iostream>
#include <cstring>
#include <openssl/bio.h>
#include <cstdio>

using namespace std;

int main()
{
	BIO *b = NULL;
	int len = 0, outlen = 0;
	char *out = NULL;

	b = BIO_new_file("./bf.txt", "w");
	len = BIO_write(b, "openssl", 7);
	len = BIO_printf(b, "%s", "zcp");
	//cout << BIO_ctrl_pending(b) << endl;
	BIO_free(b);

	b = BIO_new_file("./bf.txt", "r");
	len = BIO_pending(b);
	cout << "BIO_pending() : " << len << endl;
	len = 50;
	out = (char *)OPENSSL_malloc(len);
	memset(out, 0, len);
	len = 1;
	while (len > 0)
	{
		len = BIO_read(b, out + outlen, 1);
		outlen += len;
	}
	BIO_free(b);
	cout << out << endl;
	free(out);

	return 0;
}
