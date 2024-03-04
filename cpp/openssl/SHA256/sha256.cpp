#include <iostream>
#include <openssl/sha.h>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

bool calculateSHA256(const std::string& stream, std::string& sha256)
{
	int ret = 0;

	SHA256_CTX sha256ctx;
	ret = SHA256_Init(&sha256ctx);
	if (ret != 1)
	{
		cout << "call SHA256_Init() failed, ret code: " << ret << endl;
		return false;
	}

	ret = SHA256_Update(&sha256ctx, stream.c_str(), stream.size());
	if (ret != 1)
	{
		cout << "call SHA256_Update() failed, ret code: " << ret << endl;
		return false;
	}

	unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
	ret = SHA256_Final(hash, &sha256ctx);
	if (ret != 1)
	{
		cout << "call SHA256_Final() failed, ret code: " << ret << endl;
		return false;
	}

	std::stringstream ss;
	for (int i = 0; i != SHA256_DIGEST_LENGTH; ++i)
	{
		ss << std::setfill('0') << std::setw(2) << std::hex << (int)hash[i];
	}

	sha256.assign(ss.str());
	return true;
}

int main()
{
	std::stringstream ms;
	ifstream fin("./file_sha256.txt", std::ios_base::binary | std::ios_base::in);
	if (!fin.is_open())
	{
		cout << "open file failed." << endl;
		return -1;
	}
	ms << fin.rdbuf();

	string sha256;
	if (!calculateSHA256(ms.str(), sha256))
	{
		cout << "call calculateSHA256 failed." << endl;
		return -1;
	}

	cout << sha256 << endl;
}








