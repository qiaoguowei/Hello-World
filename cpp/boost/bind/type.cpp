#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;

int main()
{
	int a = 10;
	string b = "test";
	auto f = boost::bind(boost::type<int>(), [&](){
		cout << "a = " << a << ", b = " << b << endl; 
		return a;
	});

	auto x = f(a);
	cout << "x = " << x << endl;
}
