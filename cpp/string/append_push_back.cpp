#include <iostream>
#include <string>

using namespace std;

int main()
{
	std::string result;

	result.append("a");
	result.push_back('b');

	cout << result << endl;
}
