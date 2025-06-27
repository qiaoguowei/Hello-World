#include <iostream>
#include <list>

using namespace std;

int main()
{
	std::list<int> numList;
	std::list<int> numList2;
	numList.push_back(1);
	numList.push_back(5);
	numList.push_back(9);
	numList2.push_back(2);
	numList2.push_back(4);
	numList2.push_back(5);
	numList2.push_back(10);

	cout << "numList: ";
	for(const auto& x : numList)
	{
		cout << x << ", ";
	}
	cout << endl;

	cout << "numList2: ";
	for(const auto& x : numList2)
	{
		cout << x << ", ";
	}
	cout << endl;

	numList.insert(numList.begin(), numList2.begin(), numList2.end());
	cout << "numList: ";
	for(const auto& x : numList)
	{
		cout << x << ", ";
	}
	cout << endl;

	numList.sort();
	numList.unique([](int a, int b){return a == b;}); //先排序，去重只比较相邻的两个成员
	cout << "numList: ";
	for(const auto& x : numList)
	{
		cout << x << ", ";
	}
	cout << endl;
}
