#include <iostream>
#include <openssl/rand.h>

using namespace std;

int main(int argc, char *argv[])
{
	cout << "First openssl code!" << endl;
	time_t t = ::time(NULL);
	unsigned char buf[16] = {};
	int re = RAND_bytes(buf, sizeof(buf));
	for (int i = 0; i < sizeof(buf); i++)
	{
		cout << "[" << (int)buf[i] << "]";
	}
	cout << endl;

	
}









