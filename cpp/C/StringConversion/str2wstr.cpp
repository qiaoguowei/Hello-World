#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <locale.h>
#include <boost/scope_exit.hpp>

#ifndef BUFLEN
#define BUFLEN 256
#endif

void printhex(const std::string& str)
{
	char buf[BUFLEN];
	memset(buf, 0, BUFLEN);
	std::cout << "input string is: " << str << std::endl;
	for(size_t i = 0; i < str.size(); i++)
	{
		snprintf(buf + strlen(buf), BUFLEN - 1 - strlen(buf), "0x%x ", (unsigned char)str[i]);
	}

	std::cout << buf << std::endl;
}

std::string wstr2str(const wchar_t * src, size_t length)
{
	std::string cur_locale = setlocale(LC_ALL, NULL);
	std::cout << cur_locale << std::endl;
	setlocale(LC_ALL, "chs");
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

	setlocale(LC_ALL, cur_locale.c_str());
	return value;
}

std::wstring str2wstr(const char * src, size_t length)
{
	std::string cur_locale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs");
	std::wstring result;
	size_t buffer_size = (length + 1) * sizeof(wchar_t);
	wchar_t *dst = new wchar_t[buffer_size];
	if(dst == NULL)
	{
		std::cout << "new space failed." << std::endl;
		return result;
	}
	BOOST_SCOPE_EXIT(&dst)
	{
		if(dst != NULL)
		{
			std::cout << "--BOOST_SCOPE_EXIT--" << std::endl;
			delete []dst;
		}
	}BOOST_SCOPE_EXIT_END

	wmemset(dst, 0, buffer_size);

	mbstowcs(dst, src, buffer_size);
	result = dst;

	setlocale(LC_ALL, cur_locale.c_str());
	return result;
}

int main()
{
	std::string str1 = "abc";
	std::wstring str2;
	str2 = str2wstr(str1.c_str(), str1.size());
	std::string str3 = wstr2str(str2.c_str(), str2.size());
	printhex(str1);
	printhex(str3);
}
