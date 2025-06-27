#include <iostream>
#include <sstream>
#include <string>
#include <string.h>

using namespace std;

int main()
{
	string str1 = "aaaaaaaaa\nbbbbbbbbbbb\nccccccccc\n";
	char line[256];
	memset(line, 0, sizeof(line));
	std::istringstream iss(str1);
	iss.getline(line, sizeof(line) - 1);

	cout << str1 << endl;
	cout << line << endl;
}
