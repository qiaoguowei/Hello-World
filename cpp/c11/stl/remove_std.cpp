#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

void test1()
{
	std::list<int> coll;

	for (int i = 1; i <= 6; ++i)
	{
		coll.push_front(i);
		coll.push_back(i);
	}

	cout << "pre  : ";
	std::copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;

	remove(coll.begin(), coll.end(), 3);

	cout << "post : ";
	std::copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

void test2()
{
	list<int> coll;

	for (int i = 1; i <= 6; ++i)
	{
		coll.push_front(i);
		coll.push_back(i);
	}

	std::copy(coll.cbegin(), coll.cend(), std::ostream_iterator<int>(cout, " "));
	cout << endl;

	list<int>::iterator end = std::remove(coll.begin(), coll.end(), 3);

	std::copy(coll.begin(), end, std::ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "number of remove elements : " << distance(end, coll.end()) << endl;

	coll.erase(end, coll.end());
	std::copy(coll.cbegin(), coll.cend(), std::ostream_iterator<int>(cout, " "));
	cout << endl;
}

int main()
{
	list<int> coll;

	for (int i = 1; i <= 6; ++i)
	{
		coll.push_front(i);
		coll.push_back(i);
	}

	std::copy(coll.cbegin(), coll.cend(), std::ostream_iterator<int>(cout, " "));
	cout << endl;

	coll.erase(std::remove(coll.begin(), coll.end(), 3), coll.end());

	std::copy(coll.cbegin(), coll.cend(), std::ostream_iterator<int>(cout, " "));
	cout << endl;
}









