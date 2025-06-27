#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

int main()
{
	std::shared_ptr<char> testbuf(new char[10], [](char *buf)
												{
													if(buf != NULL)
													{
														cout << "free buf." << endl;
														delete [] buf;
													}
												});
	strncpy(testbuf.get(), "abcdefgh", 8);
	cout << testbuf << endl;
}
