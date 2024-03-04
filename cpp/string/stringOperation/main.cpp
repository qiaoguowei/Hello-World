#include <iostream>
#include "stringOperation.h"
#include <string>

using namespace std;

void test_split()
{
	string str = "aaa|+|bbb|+|ccc|+|ddd|+|eee|+|fff";
	string delimiters = "|+|";
	vector<string> tokens;

	StringOperation::stringSplit(str, delimiters, tokens);
	cout << tokens.size() << endl;
	cout << str << endl;
	for (const auto& x : tokens)
	{
		cout << x << " ";
	}
	cout << endl;
}

int main()
{
	test_split();
}
