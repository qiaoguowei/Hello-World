#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void vector_print(vector<int>& coll)
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
	vector<int> coll = {2, 5, 4, 1, 6, 3};

	auto minpos = std::min_element(coll.begin(), coll.end());
	cout << "min : " << *minpos << endl;
	auto maxpos = std::max_element(coll.begin(), coll.end());
	cout << "max : " << *maxpos << endl;

	std::sort(coll.begin(), coll.end());
	vector_print(coll);

	auto pos3 = std::find(coll.begin(), coll.end(), 3);

	reverse(pos3, coll.end());//将区间内的元素反转放置
	vector_print(coll);

	reverse(coll.begin(), coll.end());
	vector_print(coll);
}
