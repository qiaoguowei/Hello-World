#include <iostream>
#include <boost/scope_exit.hpp>

using namespace std;

void test1()
{
	string exit_str = "this function is end.";
	BOOST_SCOPE_EXIT(&exit_str)
	{
		cout << exit_str << endl;
	}BOOST_SCOPE_EXIT_END

	cout << "test1 is will end." << endl;
}

void test2()
{
	string exit_str = "this function is end.";
	//BOOST_SCOPE_EXIT(&exit_str, [](string bb){cout << bb << endl;});

	cout << "test2 is will end." << endl;
}

int main()
{
	test1();
	//test2();

	cout << "main is will end." << endl;
}
