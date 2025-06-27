#include <iostream>
#include <set>
#include <iterator>

using namespace std;

int main()
{
	set<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	std::copy(coll.cbegin(), coll.cend(), std::ostream_iterator<int>(cout, " "));
	cout << endl;

	int num = coll.erase(3);

	cout << "number of remove elements : " << num << endl;

	std::copy(coll.cbegin(), coll.cend(), std::ostream_iterator<int>(cout, " "));
	cout << endl;
}
