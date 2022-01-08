#include <iostream>
#include <backtrace.hpp>

int main()
{
	std::backtrace bt;
	std::cout << bt.trace() << std::endl;
}
