#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * template< class ForwardIt > void rotate( ForwardIt first, ForwardIt n_first, ForwardIt last 
 * 将区间[first, n_first)平移到 区间[n_first, last)后面
 *
 *
 *
 * */

int main()
{
	std::vector<int> ve = {1, 2, 3, 4, 5, 6};

	std::rotate(ve.begin(), ve.begin() + 2, ve.end() - 2);
	for (const auto& x : ve)
	{
		cout << x << " ";
	}
	cout << endl;
}
