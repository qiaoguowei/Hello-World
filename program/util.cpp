#include <iostream>
#include <utility>
#include <cstring>
#include <string>

class BypassRequestCode
{
public:
	BypassRequestCode();
	BypassRequestCode(std::string display);
private:
	friend std::ostream& operator<<(std::ostream &os, const BypassRequestCode& br_code);
	unsigned char m_buf[24];
};

BypassRequestCode::BypassRequestCode()
{
	::memset(m_buf, 0, sizeof(m_buf));
}

BypassRequestCode::BypassRequestCode(std::string display)
{
	if(display.size() == sizeof(m_buf))
	{
		::memcpy(m_buf, display.c_str(), display.size());
	}
}

std::ostream& operator<<(std::ostream &os, const BypassRequestCode& br_code)
{
	os << br_code.m_buf;
	return os;
}

class BypassCode
{
public:
	BypassCode();
	//BypassCode(std::string display);
	//void print(BypassRequestCode &request_code, int a, char b, std::string c);
	void print(std::string &request_code, int a, char b, std::string c);
private:
};

BypassCode::BypassCode()
{
}

//void BypassCode::print(BypassRequestCode &request_code, int a, char b, std::string c)
void BypassCode::print(std::string &request_code, int a, char b, std::string c)
{
	std::cout << request_code << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;

}

template<typename...Args>
void m_print(Args... args)
{
	BypassCode bc;
	//bc.print(std::forward<Args&&>(args)...);
	bc.print(args...);
}

int main()
{
	std::string str1 = "1234567890abcdefghijklmn";
	m_print<std::string>(str1, 123, 'A', "hello");
}





