#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
	std::vector<int> ve = {1, 2, 3, 4, 5, 6};

	auto it = ve.begin();
	auto nt = std::next(it);
	cout << *nt << endl;

	auto nt2 = std::next(it, 2);
	cout << *nt2 << endl;
}
