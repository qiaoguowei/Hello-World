#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using std::cout;
using std::endl;

std::string BinToHex(const std::string &strBin, bool bIsUpper)
{
	std::string strHex;
	strHex.resize(strBin.size() * 2); 
	for(size_t i = 0; i < strBin.size(); i++)
	{   
		uint8_t cTemp = strBin[i];
		for(size_t j = 0; j < 2; j++)
		{   
			uint8_t cCur = (cTemp & 0x0f);
			if(cCur < 10) 
			{   
				cCur += '0';
			}   
			else
			{   
				cCur += ((bIsUpper ? 'A' : 'a') - 10);
			}   
			strHex[2 * i + 1 - j] = cCur;
			cTemp >>= 4;
		}   
	}   
	return strHex;
}

int main()
{
	std::ifstream fin;
	fin.open("c6ccf4bdb825d890452ac17198a097e7", std::ifstream::binary);
	if(!fin.is_open())
	{
		cout << "open /home/qgw/bff9a686cb23d7f19a12d7df39030450.dat failed." << endl;
		return -1;
	}

	std::ofstream fon;
	fon.open("./restore.dat", std::ifstream::binary);
	if(!fon.is_open())
	{
		cout << "open restore.dat failed." << endl;
		fin.close();
		return -1;
	}

	char *readbuf = new char[8];
	cout << "111111111" << endl;
	while(!fin.eof())
	{
		memset(readbuf, 0, sizeof(readbuf));
		fin.read(readbuf, 1);
		cout << BinToHex(std::string(readbuf), true) << " ";
		if(readbuf[0] != 10)
			readbuf[0] ^= 0xc6;	
		fon.write(readbuf, 1);
		//cout << BinToHex(std::string(readbuf), true) << " ";
	}
	cout << endl;
	if(fin.is_open())
		fin.close();
	if(fon.is_open())
		fon.close();

	delete [] readbuf;
}



