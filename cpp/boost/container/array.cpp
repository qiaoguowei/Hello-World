#include <iostream>
#include <boost/array.hpp>

//using namespace boost;

void m_foreach_print(boost::array<int, 10>& ar)
{
	for(auto x : ar)
		std::cout << x << ", ";
	std::cout << std::endl;
}

int main()
{
	boost::array<int, 10> ar;

	ar[0] = 1;
	ar.back() = 10;
	std::cout << ar.max_size() << std::endl;
	std::cout << ar[ar.max_size() - 1] << std::endl;

	ar.assign(777);
	m_foreach_print(ar);

	int *p = ar.c_array();
	*(p + 5) = 253;
	m_foreach_print(ar);

	ar.at(8) = 666;
	std::sort(ar.begin(), ar.end());
	m_foreach_print(ar);
}
