#include <iostream>
#include <openssl/des.h>
#include <fstream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
	string cmd = "加密文件：crypt_file 输入文件名 输出文件名 密码(6)\n";
	cmd += "解密文件：crypt_file 输入文件名 输出文件名 密码(6) 1\n";
	cout << cmd << endl;
	if (argc < 4)
	{
		cerr << "param error" << endl;
		return -1;
	}

	string in_file = argv[1];	//输入文件
	string out_file = argv[2];	//输出文件
	string passwd = argv[3];	//密钥
	int is_encrypt = DES_ENCRYPT;	//加密
	if (argc > 4)
	{
		is_encrypt = DES_DECRYPT;	//解密
	}

	//二进制打开文件
	ifstream ifs(in_file, ios::binary);
	if (!ifs)
	{
		cout << "open in file failed." << endl;
		return -1;
	}

	//二进制打开输出文件
	ofstream ofs(out_file, ios::binary);
	if (!ofs)
	{
		ifs.close();
		cout << "open out file failed." << endl;
		return -1;
	}

	//处理密钥，多出丢掉，少出补0
	int key_size = passwd.size();
	const_DES_cblock key = {};
	if (key_size > sizeof(key))
		key_size = sizeof(key);

	memcpy(key, passwd.c_str(), key_size);
	DES_key_schedule key_sch;

	DES_set_key(&key, &key_sch); //设置密钥

	const_DES_cblock in; //输入数据
	DES_cblock out;		//输出数据

	//获取文件大小
	long long file_size = 0;
	ifs.seekg(0, ios::end);//文件指针移到结尾
	file_size = ifs.tellg();
	ifs.seekg(0, ios::beg);
	cout << "file size = " << file_size << endl;

	long long read_size = 0;
	long long write_size = 0;

	//读文件，加解密文件，写入文件
	while (!ifs.eof())
	{
		int out_len = sizeof(out);
		//读文件
		ifs.read((char *)in, sizeof(in));
		int count = ifs.gcount();
		if(count <= 0)
			break;
		read_size += count;

		//PKCS7 padding 填充
		//加密到结尾处填充
		if (read_size == file_size && is_encrypt == DES_ENCRYPT)
		{
			if (file_size % 8 == 0) //填充8字节的值为8
			{
				DES_ecb_encrypt(&in, &out, &key_sch, is_encrypt);
				ofs.write((char *)out, out_len);

				//填充数据 8
				memset(in, 8, sizeof(in));
			}
			else
			{
				int padding = 8 - file_size % 8; //要填充的字节
				//移到位置填充数据
				memset(in + (file_size % 8), padding, padding);
			}
		}

		//加解密文件
		DES_ecb_encrypt(&in, &out, &key_sch, is_encrypt);

		//解密结尾处padding
		if (read_size == file_size && is_encrypt == DES_DECRYPT)
		{
			//减去填充大小
			out_len = 8 - out[7];
		}
		if (out_len <= 0)
			break;

		//写入文件
		ofs.write((char *)out, out_len);
		write_size += out_len;

	}


	ifs.close();
	ofs.close();
	cout << "write size : " << write_size << endl;

	return 0;
}









