#include <iostream>
#include <boost/algorithm/string/case_conv.hpp>

namespace ba = boost::algorithm;

int main()
{
	std::string work_mode = "offline@qq.com";
	std::string mode = boost::to_upper_copy(work_mode);

	std::cout << "work_mode: " << work_mode << std::endl;
	std::cout << "mode: " << mode << std::endl;
}
