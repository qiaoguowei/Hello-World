#include <iostream>
#include <string>
#include <chrono>

using namespace std;

int main()
{
	std::chrono::seconds twentySeconds(20);
	std::chrono::hours aDay(24);

	std::chrono::milliseconds ms;
	ms += twentySeconds + aDay;
	--ms;

	ms *= 2;
	cout << twentySeconds.count() << " s" << endl;
	cout << aDay.count() << " h" << endl;
	cout << ms.count() << " ms" << endl;
	cout << std::chrono::nanoseconds(ms).count() << " ns" << endl;
}
