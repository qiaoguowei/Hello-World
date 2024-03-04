#include <iostream>
#include <utility>

int main()
{
	typedef std::pair<int, float> IntFloatPair;
	IntFloatPair p(42, 3.14);

	std::cout << std::get<0>(p) << std::endl;
	std::cout << std::get<1>(p) << std::endl;
	std::cout << std::tuple_size<IntFloatPair>::value << std::endl;
	//std::cout << std::tuple_element<0, IntFloatPair>::type << std::endl;
}
