#include <iostream>
#include <cstdio>
#include <cstring>
#include <openssl/bio.h>

using namespace std;

int main()
{
	BIO *b = NULL;
	BIO *c = NULL;
	int sock, ret, len;
	char *addr = NULL;
	char out[80];

	sock = BIO_get_accept_socket("2323", 0);
	b = BIO_new_socket(sock, BIO_NOCLOSE);
	ret = BIO_accept(sock, &addr);
	BIO_set_fd(b, ret, BIO_NOCLOSE);

	while (1)
	{
		memset(out, 0, sizeof(out));
		len = BIO_read(b, out, sizeof(out));
		if (out[0] == 'q')
			break;
		cout << out << endl;
	}

	BIO_free(b);
	return 0;
}
