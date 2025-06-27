#include <iostream>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	std::multimap<int, string> mm1;
	std::multimap<int, string> mm2;

	mm1.insert(std::make_pair(1, "aaa"));
	mm1.insert(std::make_pair(2, "bbb"));
	mm1.insert(std::make_pair(3, "ccc"));
	mm2.insert(std::make_pair(1, "aaa"));
	mm2.insert(std::make_pair(2, "bbb"));
	mm2.insert(std::make_pair(3, "ccc"));
	mm2.insert(std::make_pair(4, "ddd"));

	if (std::equal(mm1.begin(), mm1.end(), mm2.begin()))
	{
		cout << "map1 == map2" << endl;
		return 0;
	}
	cout << "map1 != map2" << endl;
	return 0;
}
