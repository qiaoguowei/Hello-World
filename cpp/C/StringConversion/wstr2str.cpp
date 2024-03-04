#include <iostream>
#include <cstdlib>
#include <string>
#include <boost/scope_exit.hpp>

std::string wstr2str(const wchar_t * src, size_t length)
{
	std::string value;
	char *dst = NULL;
	size_t buffer_size;
	if(length <= 0)
		return value;

	buffer_size = length * sizeof(wchar_t) + 1;
	dst = new char[buffer_size];
	if(dst == NULL)
	{
		std::cout << "new space failed." << std::endl;
		return value;
	}
	BOOST_SCOPE_EXIT(&dst)
	{
		if(dst != NULL)
			delete []dst;
		std::cout << "--BOOST_SCOPE_EXIT--" << std::endl;
	}BOOST_SCOPE_EXIT_END
	
	memset(dst, 0, buffer_size);
	wcstombs(dst, src, buffer_size);
	value = dst;

	return value;
}

int main()
{
	std::wstring wstr = L"我是谁abcdefg";
	std::string ret_str = wstr2str(wstr.c_str(), wstr.size());
	std::wcout << wstr << std::endl;
	std::cout << ret_str << std::endl;
}
