#include <iostream>
#include <cstdlib>
#include <functional>

using namespace std;

//typedef void (*exit_func)();

void f()
{
	cout << "calling the exit function." << endl;
}

void mAdd(int&& a, int&& b)
{
	atexit(f);//程序退出时，执行函数
	cout << a + b << endl;
}

int main()
{
	//std::function<void()> exit_func;

	//auto f = []()
	//{
	//	cout << "calling the exit function." << endl;
	//};

	//atexit(&f);
	mAdd(3, 4);

	cout << "I will exit." << endl;
}
