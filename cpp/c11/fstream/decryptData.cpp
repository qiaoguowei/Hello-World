#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "Cipherer.h"
#include "ReadOrWrite.h"

using namespace std;

int main()
{
	unsigned char *buffer;
	unsigned int bufferSize;
	string filePath = "./outFile.txt";
	if (!getDataFromFile(filePath, &buffer, bufferSize))
	{
		cout << "failed to get data from file." << endl;
		return -1;
	}
	//cout << buffer << endl;
	cout << bufferSize << endl;

	unsigned char *outputBuf;
	int outbuffersize;
	//if (!encrypt(SG_ENCRYPT_DES_ECB, buffer, bufferSize, &outputBuf, outbuffersize))
	if (!encrypt(SG_ENCRYPT_DES_CBC, buffer, bufferSize, &outputBuf, outbuffersize))
	//if (!encrypt(SG_ENCRYPT_AES_ECB, buffer, bufferSize, &outputBuf, outbuffersize))
	//if (!decrypt(SG_ENCRYPT_AES_CBC, buffer, bufferSize, &outputBuf, outbuffersize))
	{
		cout << "failed to decrypt." << endl;
		delete [] buffer;
		return -1;
	}
	delete [] buffer;
	cout << outbuffersize << endl;

	string outFilePath = "./DecryptFile.txt";
	writeDataToFile(outputBuf, outbuffersize, outFilePath);

	delete [] outputBuf;
}






