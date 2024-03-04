#include <iostream>
#include <string>

using namespace std;

class A
{
public:
	A(string a) : m_a(a) {}

protected:
	void print_a()
	{
		cout << m_a << endl;
	}

protected:
	string m_a;
};

class B : public virtual A
{
public:
	B(string a, string b) : A(a), m_b(b) {}

	void print()
	{
		print_a();
		print_b();
		cout << m_a << endl;
	}

protected:
	void print_b()
	{
		cout << m_b << endl;
	}

protected:
	string m_b;
};

int main()
{
	B _b("aaa", "bbb");

	_b.print();

	cout << sizeof(B) << endl;
	cout << sizeof(A) << endl;
}












