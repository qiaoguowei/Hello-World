#include <iostream>
#include <boost/random.hpp>
#include <time.h>
#include <boost/random/random_device.hpp>

using namespace std;

void random_int()
{
	boost::random::mt19937 gen(time(0));
	boost::uniform_int<> dis(1, 200);

	for (int i = 0; i < 10; ++i)
	{
		cout << dis(gen) << endl;
	}
}

void random_01()
{
	boost::random::mt19937 gen(time(0));
	boost::uniform_01<> dis;

	for (int i = 0; i < 10; ++i)
	{
		cout << dis(gen) << endl;
	}
}

void random_bernoulli()//抛硬币不是0就是1
{
	boost::random::mt19937 gen(time(0));
	boost::bernoulli_distribution<> dis;

	for (int i = 0; i < 10; ++i)
	{
		cout << dis(gen) << endl;
	}
}

void random_real()
{
	cout << boost::random::random_device::min() << ":" << boost::random::random_device::max() << endl;

	boost::random::random_device gen;
	for (int i = 0; i < 10; ++i)
	{
		cout << gen() << endl;
	}
}

int main()
{
	random_real();
}









