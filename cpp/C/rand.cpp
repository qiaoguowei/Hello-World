#include <iostream>
#include <stdlib.h>
#include <time.h>

int with_srand()
{
	int num = rand()%100;
	return num;
}

int main()
{
	int flag = 0;
	int num = 0;
	while(1)
	{
		std::cin >> flag;

		switch(flag)
		{
			case 1 :
				num = with_srand();
				std::cout << num << std::endl;
				break;
		}
	}
}
