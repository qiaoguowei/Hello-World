#include <iostream>
#include <string>

using namespace std;

int main()
{
	std::string str1 = "deviceConfig[0].[icapDebug]"; //find . or [
	std::string::size_type pos = 0;

	pos = str1.find_first_of(".[", pos);
	cout << str1.substr(pos) << endl;
}







