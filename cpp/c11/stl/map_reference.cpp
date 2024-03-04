#include <iostream>
#include <map>
#include <string>
#include <memory>

using namespace std;

class A
{
public:
	A(int a, string b) : mAge(a), mName(b) {}
	A() : mAge(0), mName("") {}
	int getAge()
	{
		return mAge;
	}
	void setAge(const int&& a)
	{
		mAge = a;
	}
	void setName(const string&& b)
	{
		mName = b;
	}
private:
	int mAge;
	string mName;
};

int main()
{
	std::shared_ptr<A> aa(new A());
	std::map<int, std::shared_ptr<A>> mMap;
	mMap.insert(make_pair(aa->getAge(), aa));

	auto xx = mMap.begin();
	xx->second->setAge(11);
	xx->second->setName("xxxx");
	cout << aa->getAge() << endl;
}
