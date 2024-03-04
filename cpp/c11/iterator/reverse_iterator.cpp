#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	vector<int> coll;

	for (int i = 1; i <= 9; ++i)
	{
		coll.push_back(i);
	}

	std::copy(coll.crbegin(), coll.crend(), std::ostream_iterator<int>(cout, " "));
	cout << endl;
}
