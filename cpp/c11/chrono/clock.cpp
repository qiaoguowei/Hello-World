#include <iostream>
#include <chrono>
#include <ctime>
#include <string>

using namespace std;

std::string asString(const std::chrono::system_clock::time_point& tp)
{
	time_t t = std::chrono::system_clock::to_time_t(tp);
	std::string ts = ctime(&t);
	ts.resize(ts.size()-1);
	return ts;
}

int main()
{
	std::chrono::system_clock::time_point tp;
	std::cout << "epoch: " << asString(tp) << endl;

	tp = std::chrono::system_clock::now();
	cout << "now: " << asString(tp) << endl;

	tp = std::chrono::system_clock::time_point::min();
	cout << "min: " << asString(tp) << endl;

	tp = std::chrono::system_clock::time_point::max();
	cout << "max: " << asString(tp) << endl;
}
