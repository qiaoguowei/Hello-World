#ifndef _CIPHERER_H
#define _CIPHERER_H

#include <iostream>
#include <string>
#include <cstring>
#include <openssl/evp.h>

using namespace std;

static string mKey = "beijing@skyguard!network_security";
static string mIvec = "skyguardsecurity";

enum class SG_ENCRYPT_TYPE
{
	SG_ENCRYPT_DES_ECB = 0,
	SG_ENCRYPT_DES_CBC,
	SG_ENCRYPT_AES_ECB,
	SG_ENCRYPT_AES_CBC,
	SG_ENCRYPT_UNKNOWN
};

bool encrypt(SG_ENCRYPT_TYPE type, const unsigned char *inputBuf, int inputLength,
		     unsigned char **outputBuf, int& outputLength)
{
	cout << "Cipherer, encrypt [data] ... " << endl;
	if (!inputBuf || inputLength == 0)
	{
		cout << "Cipherer, encrypt[data]:parameters are invalid." << endl;
		return false;
	}

	const unsigned char *key = (const unsigned char *)mKey.c_str();
	const unsigned char *ivec = (const unsigned char *)mIvec.c_str();
	if ((type = SG_ENCRYPT_DES_CBC) && (mIvec.size() < 8))
	{
		cout << "Cipherer, encrypt[des cbc]:ivec < 8 characters:" << mIvec << endl;
		return false;
	}
	else if ((type == SG_ENCRYPT_AES_CBC) && ((mKey.size() < 32) || (mIvec.size() < 16)))
	{
		cout << "Cipherer, encrypt[aes cbc]:ivec < 16 characters or key < 32 characters." << endl;
		return false;
	}
	else if ((type == SG_ENCRYPT_AES_ECB) && (mKey.size() < 32))
	{
		cout << "Cipherer, encrypt[aes ecb]:key < 32 characters." << endl;
		return false;
	}

#ifdef SSL_1_1
	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
	EVP_CIPHER_CTX_init(ctx);
	int ret = 0;
	switch (type)
	{
		case SG_ENCRYPT_DES_ECB:
			ret = EVP_EncryptInit_ex(ctx, EVP_des_ecb(), NULL, key, NULL);
			break;
		case SG_ENCRYPT_DES_CBC:
			ret = EVP_EncryptInit_ex(ctx, EVP_des_cbc(), NULL, key, ivec);
			break;
		case SG_ENCRYPT_AES_ECB:
			ret = EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL);
			break;
		case SG_ENCRYPT_AES_CBC:
			ret = EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, ivec);
			break;
		default:
			cout << "Encrypt type unknow, type:" << type << endl;
	}

	if (1 != ret)
	{
		cout << "Cipherer, failed to init encrypt." << endl;
		return false;
	}

	*outputBuf = new unsigned char[inputLength + EVP_MAX_KEY_LENGTH];
	memset(*outputBuf, 0x00, inputLength + EVP_MAX_KEY_LENGTH);
	if (1 != EVP_EncryptUpdate(ctx, (unsigned char *)*outputBuf, &outputLength, inputBuf, inputLength))
	{
		cout << "Cipherer, failed to process encrypt." << endl;
		EVP_CIPHER_CTX_free(ctx);
		delete []*outputBuf;
		return false;
	}

	int finalOutputLength = 0;
	if (1 != EVP_EncryptFinal_ex(ctx, *outputBuf + outputLength, &finalOutputLength))
	{
		cout << "Cipherer, failed to finalize encrypt." << endl;
		delete []*outputBuf;
		EVP_CIPHER_CTX_free(ctx);
		return false;
	}
	outputLength += finalOutputLength;
	EVP_CIPHER_CTX_free(ctx);
#else
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	int ret = 0;
	switch (type)
	{
		case SG_ENCRYPT_DES_ECB:
			ret = EVP_EncryptInit_ex(&ctx, EVP_des_ecb(), NULL, key, NULL);
			break;
		case SG_ENCRYPT_DES_CBC:
			ret = EVP_EncryptInit_ex(&ctx, EVP_des_cbc(), NULL, key, ivec);
			break;
		case SG_ENCRYPT_AES_ECB:
			ret = EVP_EncryptInit_ex(&ctx, EVP_aes_256_ecb(), NULL, key, NULL);
			break;
		case SG_ENCRYPT_AES_CBC:
			ret = EVP_EncryptInit_ex(&ctx, EVP_aes_256_cbc(), NULL, key, ivec);
			break;
		default:
			cout << "Encrypt type unknow, type:" << type << endl;
	}
	if (1 != ret)
	{
		cout << "Cipherer, failed to init decrypt." << endl;
		return false;
	}

	outputBuf = new unsigned char[inputLength + EVP_MAX_KEY_LENGTH];
	memset(*outputBuf, 0x00, inputLength + EVP_MAX_KEY_LENGTH);
	if (1 != EVP_EncryptUpdate(&ctx, (unsigned char *)*outputBuf, &outputLength, inputBuf, inputLength))
	{
		cout << "Cipherer, failed to process encrypt." << endl;
		EVP_CIPHER_CTX_cleanup(&ctx);
		delete []*outputBuf;
		return false;
	}

	int finalOutputLength = 0;
	if (1 != EVP_EncryptFinal_ex(&ctx, *outputBuf + outputLength, &finalOutputLength))
	{
		cout << "Cipherer, failed to finalize encrypt." << endl;
		delete []*outputBuf;
		EVP_CIPHER_CTX_cleanup(&ctx);
		return false;
	}
	outputLength += finalOutputLength;
	EVP_CIPHER_CTX_cleanup(&ctx);
#endif

	memset(*outputBuf + outputLength, 0x00, inputLength + EVP_MAX_KEY_LENGTH - outputLength);
	cout << "Cipherer, encrypt finished." << endl;
	return true;
}



#endif








