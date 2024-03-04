#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

struct square
{
	typedef void result_type;
	void operator()(int& x)
	{
		x = x * x;
	}
};


int main()
{
	typedef double (*pfunc)(double);
	pfunc pf = sqrt;
	cout << std::ref(pf)(5.0) << endl;

	square sq;
	int x = 5;
	std::ref(sq)(x);
	cout << x << endl;

	vector<int> v = {1, 2, 3, 4, 5};
	for_each(v.begin(), v.end(), std::ref(sq));
	for (const auto& x : v)
	{
		cout << x << " ";
	}
	cout << endl;
}
