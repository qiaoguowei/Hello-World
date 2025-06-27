#include <iostream>
#include <atomic>

using namespace std;

/*
 * bool atomic::compare_exchange_strong(T& param1, T param2, ...);
 * 当param1 == atomic.load();    atomic.store(param2);
 * 当param1 != atomic.load();    param1 = atomic.load();
 *
 *
 * */
int main()
{
	std::atomic<int> num;
	int x = 0;
	num.store(2);
	int param2 = 5;

	cout << std::boolalpha << num.compare_exchange_strong(x, param2) << endl;

	cout << num.load() << endl;
	cout << x << endl;
	cout << param2 << endl;

	cout << num.compare_exchange_strong(x, param2) << std::noboolalpha << endl;

	cout << num.load() << endl;
	cout << x << endl;
	cout << param2 << endl;
}
