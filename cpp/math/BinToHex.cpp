#include <iostream>
#include <string>

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
	std::string str1 = "32163E31A131D3AB0514FD1B128512D1CFD4C167463B73009D02B2C5E3950FCD";
	std::string strHex = BinToHex(str1, true);
	std::cout << str1 << std::endl;
	std::cout << strHex << std::endl;
}
