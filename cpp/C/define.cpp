#include <iostream>
#include <cstdio>

#define INT_TO_STR(a) #a
#define TEST(A) "abc" #A "efg"
#define HT_FIND(name) name##_HT_FIND
#define event_io_map_HT_FIND "aaaaaaaaaaaa"
using namespace std;

int main()
{
	std::string str1 = "abc";

	std::string str2 = INT_TO_STR(1);
	std::cout << str2 << std::endl;
	
	std::string str3 = TEST(d);
	std::cout << str3 << std::endl;
#if 0
    std::string str4 = HT_FIND(event_io_map);
    cout << str4 << endl;
#endif
}
