#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	std::vector<char> mResponseData = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd'};
	cout << mResponseData.data() << endl;

	std::vector<int> mNum = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	cout << mNum.data() << endl;

	std::vector<string> mString = {"aaa", "bbb", "ccc", "ddd"};
	cout << mString.data() << endl;
	cout << *mString.data() << endl;
}
