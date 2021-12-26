#include <iostream>
#include <cstdio>

#define PRINTSTR(str) printf(#str ": --%s--\n", str)
int main()
{
	char buf[128] = "abcdefg";
	PRINTSTR(buf);
}
