#include <iostream>
#include <tuple>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main()
{
	//std::tuple<int, float, std::string> t1(41, 6.3, "nico");
	auto t1 = std::make_tuple(41, 6.3, "nico");

	cout << std::get<0>(t1) << endl;
	cout << std::get<1>(t1) << endl;
	cout << std::get<2>(t1) << endl;
}
