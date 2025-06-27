#include <iostream>
#include <openssl/des.h>

using namespace std;

int main(int argc, char *argv[])
{
	unsigned char data[] = "1234567";
	unsigned char out[1024] = {};
	unsigned char out2[1024] = {};

	const_DES_cblock *key = (const_DES_cblock *)"1234567";
	DES_key_schedule key_sch;
	//设置密钥
	DES_set_key(key, &key_sch);
	//数据加密
	DES_ecb_encrypt((const_DES_cblock *)data, (DES_cblock *)out, &key_sch, DES_ENCRYPT);
	cout << out << endl;
	//数据解密
	DES_ecb_encrypt((DES_cblock *)out, (DES_cblock *)out2, &key_sch, DES_DECRYPT);
	cout << out2 << endl;
}








