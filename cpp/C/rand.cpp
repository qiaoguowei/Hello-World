#include <iostream>
#include <stdlib.h>

int main()
{
	for(int i = 0; i < 10; i++)
	{
		std::cout << rand()%10 << std::endl;
	}
}
