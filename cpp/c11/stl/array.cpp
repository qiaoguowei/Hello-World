#include <iostream>
#include <array>

using namespace std;

int main()
{
	std::array<int, 6> myarray;

	myarray.fill(5);

	cout << "myarray contains :";
	for (auto &x : myarray)
	{
		cout << " " << x;
	}
	cout << endl;

	array<int, 5> mArray = {43}; //初值列中没有足够的元素，由其类型的default构造函数初始化
	for (const auto& x : mArray)
	{
		cout << x << " ";
	}
	cout << endl;

	return 0;
}
