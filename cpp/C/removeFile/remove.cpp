#include <iostream>
#include <stdio.h>

int main()
{
	FILE *fp = nullptr;
	fp = fopen("./test.log", "w");
	if(fp == nullptr)
	{
		perror("fopen()");
		return -1;
	}
	fclose(fp);

	std::cout << "the file is open." << std::endl;

	int ret = ::remove("./test.log");
	if(ret != 0)
	{
		perror("remove()");
		return -1;
	}
	return 0;
}
