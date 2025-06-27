#include <iostream>
#include <openssl/bio.h>
#include <cstdio>

using namespace std;

int main()
{
	BIO *b = NULL;
	int len = 0;
	char *out = NULL;

	b = BIO_new(BIO_s_mem());
	len = BIO_write(b, "openssl", 7);
	cout << len << endl;

	len = BIO_printf(b, "%s", "zcp");
	cout << len << endl;

	len = BIO_ctrl_pending(b);
	cout << len << endl;

	out = (char *)OPENSSL_malloc(len);
	len = BIO_read(b, out, len);
	cout << out << endl;
	OPENSSL_free(out);
	BIO_free(b);
	return 0;
}
