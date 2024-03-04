#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int square(int value)
{
	return value * value;
}

int main()
{
	std::set<int> coll1;
	std::vector<int> coll2;

	for (int i = 1; i <= 9; ++i)
	{
		coll1.insert(i);
	}

	for (auto& x : coll1)
	{
		cout << x << " ";
	}
	cout << endl;

	std::transform(coll1.cbegin(), coll1.cend(), std::back_inserter(coll2), square);

	for (auto& x : coll2)
	{
		cout << x << " ";
	}
	cout << endl;
}
















