#include <iostream>
#include <cstring>

int main()
{
	char buf[20] = {0};
	
	memset(buf, '1', sizeof(buf)-1);
	std::cout << buf << std::endl;
}
