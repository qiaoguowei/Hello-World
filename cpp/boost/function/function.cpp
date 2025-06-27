#include <iostream>
#include <boost/function.hpp>

using namespace std;

//可以存储bind/lambda表达式的结果，使bind/lambda能被多次调用

int f(int a, int b)
{
	return a + b;
}

void test1()
{
	boost::function<int(int, int)> func;
	func = f;
	if (func)
	{
		cout << func(20, 30) << endl;
	}

	func = 0; //把function清空，相当于clear()
	cout << func.empty() << endl;
}

int main()
{
	test1();                                                
}
