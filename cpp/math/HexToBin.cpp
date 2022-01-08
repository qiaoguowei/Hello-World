#include <iostream>
#include <string>

std::string HexToBin(const std::string &strHex)
{
	if(strHex.size() % 2 != 0)
	{
		return "";
	}

	std::string strBin;
	strBin.resize(strHex.size() / 2);
	for(size_t i = 0; i < strBin.size(); i++)
	{
		uint8_t cTemp = 0;
		for(size_t j = 0; j < 2; j++)
		{
			char cCur = strHex[2 * i + j];
			if(cCur >= '0' && cCur <= '9')
			{
				cTemp = (cTemp << 4) + (cCur - '0');
			}
			else if(cCur >= 'a' && cCur <= 'f')
			{
				cTemp = (cTemp << 4) + (cCur - 'a' + 10);
			}
			else if(cCur >= 'A' && cCur <= 'F')
			{
				cTemp = (cTemp << 4) + (cCur - 'A' + 10);
			}
			else
			{
				return "";
			}
		}
		strBin[i] = cTemp;
	}
	return strBin;
}

int main()
{
	std::string str1 = "61626364313039383736";
	std::string strBin = HexToBin(str1);
	std::cout << str1 << std::endl;
	std::cout << strBin << std::endl;
}
















