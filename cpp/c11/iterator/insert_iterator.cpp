#include <iostream>
#include <algorithm>
#include <set>
#include <iterator>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <sstream>

using namespace std;

template<typename T>
void collection_print(T& coll)
{
	std::string m_print;
	std::stringstream m_conver;
	for (auto& x : coll)
	{
		m_conver << x << ", ";
	}
	m_print = m_conver.str();
	m_print = m_print.substr(0, m_print.size() - 2);
	cout << m_print << endl;
}

int main()
{
	std::list<int> coll1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	vector<int> coll2;
	std::copy(coll1.cbegin(), coll1.cend(), back_inserter(coll2));
	collection_print<vector<int>>(coll2);

	deque<int> coll3;
	std::copy(coll1.cbegin(), coll1.cend(), front_inserter(coll3));
	collection_print<deque<int>>(coll3);

	set<int> coll4;
	std::copy(coll1.cbegin(), coll1.cend(), inserter(coll4, coll4.begin()));
	collection_print<set<int>>(coll4);
}







