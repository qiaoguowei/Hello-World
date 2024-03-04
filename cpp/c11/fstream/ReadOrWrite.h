#ifndef _READORWRITE_H
#define _READORWRITE_H

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

bool getDataFromFile(const string& filePath, unsigned char **buffer, unsigned int& bufferSize)
{
	std::ifstream fileStream(filePath, std::ios::binary);
	if (!fileStream)
	{
		cout << "failed to open the file." << endl;
		return false;
	}

	std::istream::pos_type beginPos = fileStream.tellg();
	fileStream.seekg(0, std::ios_base::end);
	unsigned int fileSize = fileStream.tellg();
	fileStream.seekg(beginPos);

	bufferSize = fileSize;
	*buffer = new unsigned char[bufferSize];
	memset(*buffer, 0x00, bufferSize);
	if (!(*buffer))
	{
		cout << "failed to allocate memory." << endl;
		return false;
	}

	unsigned int readBytes = 0;
	while (!fileStream.eof() && readBytes < fileSize)
	{
		fileStream.read((char *)(*buffer) + readBytes, fileSize - readBytes);
		if (fileStream.fail())
		{
			cout << "failed to read data from file stream." << endl;
			return false;
		}
		readBytes += fileStream.gcount();
	}
	fileStream.close();

	return true;
}

bool writeDataToFile(const unsigned char *buffer, const unsigned int bufferSize, const string& filePath)
{
	std::ofstream fileStream(filePath, std::ios::binary);
	if (!fileStream)
	{
		cout << "Cipherer, failed to open the output file." << endl;
		return false;
	}

	fileStream.write((const char *)buffer, bufferSize);
	if (fileStream.fail())
	{
		cout << "Cipherer, failed to write data to file stream." << endl;
		return false;
	}
	fileStream.close();

	return true;
}




#endif





