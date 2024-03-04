#include <iostream>
#include <boost/ref.hpp>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

/*
 * reference_wrapper<T> ref(T& t);
 * reference_wrapper<T const> cref(T const& t);
 *
 * */
void m_unwrap_ref() //解开一个包装，返回被包装对象的引用。没有被包装的对象直接返回自身的引用
{
	cout << "------------------------------m_unwrap_ref()-------------------" << endl;
	std::set<int> s;
	auto w = boost::ref(s);
	unwrap_ref(w).insert(12);
	cout << *s.begin() << endl;

	string str("test");
	auto rws = boost::cref(str);
	cout << unwrap_ref(rws) << endl;
}

void is_wrap()
{
	cout << "---------------------------is_wrap()--------------------" << endl;
	vector<int> v(10, 2);
	auto rw = boost::cref(v);

	cout << boost::is_reference_wrapper<decltype(rw)>::value << endl; //return bool 是否被ref包装
	cout << boost::is_reference_wrapper<decltype(v)>::value << endl;

	string str;
	auto rws = boost::ref(str);
	cout << typeid(boost::unwrap_reference<decltype(rws)>::type).name() << endl; //return 变量的真实类型
	cout << typeid(boost::unwrap_reference<decltype(str)>::type).name() << endl;
}

void m_instance()
{
	double x = 2.0;
	cout << std::sqrt(boost::ref(x)) << endl; //平方根
}

void ref_cref()
{
	double x = 2.71828;
	auto rw = boost::cref(x);
	cout << typeid(rw).name() << endl;

	string str;
	auto rws = boost::ref(str);
	cout << typeid(rws).name() << endl;
}

int main()
{
	int x = 10;
	boost::reference_wrapper<int> rw(x);
	cout << rw.get() << endl;

	string str1;
	boost::reference_wrapper<string> rws(str1);
	*rws.get_pointer() = "test reference_wrapper";
	cout << str1 << endl;

	ref_cref();
	m_instance();
	is_wrap();
	m_unwrap_ref();
}
