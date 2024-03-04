#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main()
{
	vector<string> coll = {"aaa", "bbb", "ccc", "ddd", "bbb"};

	//std::copy(std::istream_iterator<string>(cin),
	//		  std::istream_iterator<string>(),
	//		  back_inserter(coll));

	std::sort(coll.begin(), coll.end());

	std::unique_copy(coll.cbegin(), coll.cend(), ostream_iterator<string>(cout, "\n"));
}
