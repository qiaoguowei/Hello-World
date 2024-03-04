#include <iostream>
#include <boost/signals2.hpp>

using namespace std;
//using namespace boost::signals2;

void slots1()
{
	cout << "slot1 called" << endl;
}

void slots2()
{
	cout << "slot2 called" << endl;
}

void test1()
{
	boost::signals2::signal<void()> sig;

	sig.connect(&slots1);
	sig.connect(&slots2);//第二个参数，默认值at_back
	sig();
}

void test2()
{
	boost::signals2::signal<void()> sig;

	sig.connect(&slots1, boost::signals2::at_front);
	sig.connect(&slots2, boost::signals2::at_front);//第二个参数，默认值at_back
	sig();
}

//========================================================================================

template<int N>
struct slots
{
	void operator()()
	{
		cout << "slot" << N << "called" << endl;
	}
};

void test3()
{
	boost::signals2::signal<void()> sig;
	sig.connect(slots<1>(), boost::signals2::at_back);
	sig.connect(slots<100>(), boost::signals2::at_front);

	sig.connect(5, slots<51>(), boost::signals2::at_back);
	sig.connect(5, slots<55>(), boost::signals2::at_front);
	sig.connect(3, slots<30>(), boost::signals2::at_front);
	sig.connect(3, slots<33>(), boost::signals2::at_back);
	sig.connect(10, slots<10>(), boost::signals2::at_back);

	sig();
}

//=================================传参，返回值=======================================================

template<int N>
struct m_slots
{
	int operator()(int x)
	{
		cout << "slot" << N << " called" << endl;
		return x * N;
	}
};

void test4()
{
	boost::signals2::signal<int(int)> sig;

	sig.connect(m_slots<10>());
	sig.connect(m_slots<20>());
	sig.connect(m_slots<50>());

	cout << *sig(5) << endl;
}

int main()
{
	test4();
}
