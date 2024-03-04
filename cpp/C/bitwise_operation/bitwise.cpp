#include <iostream>

using namespace std;

#define GET_EVENT_APP(et)  ((unsigned char)(((unsigned short)((et) >> 16) & 0xFFFF) >> 8) & 0xFF)
#define GET_EVENT_MOD(et)  ((unsigned char)((unsigned short)((et) >> 16) & 0xFFFF) & 0xFF)
#define GET_EVENT_TYPE(et) ((unsigned short)((et)) & 0xFFFF)


int main()
{
	unsigned int et = 0x1020014;

	cout << GET_EVENT_APP(et) << endl;
	cout << GET_EVENT_MOD(et) << endl;
	cout << GET_EVENT_TYPE(et) << endl;
}

