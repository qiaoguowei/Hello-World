#include <iostream>
#include <string>

//std::string replace(size_t pos, int num, std::string name, size_t num_begin, int size);
//从pos开始的num个字符替换成name从num_begin开始的size个字符

int main()
{
	std::string str1 = "DLPServer.components.component[name=\"*****\"].IsStart";
	size_t pos = str1.find_first_of('*');
	std::string name = "DSA";
	auto& x = str1.replace(pos, 5, name, 0, name.size());
	
	std::cout << str1 << std::endl;
	std::cout << x << std::endl;
}
