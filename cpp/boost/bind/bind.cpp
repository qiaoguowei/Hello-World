#include <iostream>
#include <algorithm>
#include <boost/bind.hpp>
#include <vector>

using namespace std;

/*
 * bind<result_type>(function, ...);
 * */

int f(int a, int b)
{
	return a + b;
}

int g(int a, int b, int c)
{
	return a + b + c;
}

void general_func()
{
	cout << boost::bind(f, 1, 2)() << endl;
	cout << boost::bind(g, 1, 2, 3)() << endl;
	cout << boost::bind(f, _1, _2)(2, 3) << endl;
}

//=========================================================================
void func_point()
{
	typedef decltype(&f) f_type;
	typedef decltype(&g) g_type;

	f_type pf = f;
	g_type pg = g;

	int x = 1, y = 2, z = 3;

	cout << bind(pf, _1, 9)(x) << endl;
	cout << bind(pg, _3, _2, _2)(x, y, z) << endl;   //(*pg)(z, y, y);
}
//=============================================================================
struct demo
{
	int f(int a, int b)
	{
		return a + b;
	}
};

void class_func()
{
	demo a;
	demo &ra = a;
	demo *p = &a;

	cout << bind(&demo::f, a, _1, 20)(10) << endl; //必须在成员函数前加去地址操作符&,表明这是一个成员函数指针
	cout << bind(&demo::f, ra, _2, _1)(10, 20) << endl;
	cout << bind(&demo::f, p, _1, _2)(10, 20) << endl;
}

//=================================================================================
struct point
{
	int x;
	int y;
	point(int a = 0, int b = 0) : x(a), y(b) {}
	void print()
	{
		cout << "(" << x << "," << y << ")\n";
	}
};

void class_variable()
{
	vector<point> v(10);
	vector<int> v2(10);
	transform(v.begin(), v.end(), v2.begin(), bind(&point::x, _1));

	for(const auto& x : v2)
	{
		cout << x << ", ";
	}
	cout << endl;
}
//=================================================================================
//对于自定义对象，如果没有result_type类型的定义，需要在模板参数指定返回值类型
struct func
{
	int operator()(int a, int b)
	{
		return a + b;
	}
};


struct func2
{
	typedef int result_type;
	int operator()(int a, int b)
	{
		return a + b;
	}
};

void owner_class()
{
	cout << boost::bind(func2(), _1, _2)(10, 20) << endl;
}

int main()
{
	//general_func();
	//func_point();
	//class_func();
	//class_variable();
	owner_class();
}





