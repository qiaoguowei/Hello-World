#include <iostream>
#include <boost/smart_ptr.hpp>

class self_shared : public boost::enable_shared_from_this<self_shared>
{
public:
	self_shared(int n) : x(n) {}
	int x;
	void print()
	{
		std::cout << "self_shared: " << x << std::endl;
	}
private:
	//int x;
};

int main()
{
	auto sp = boost::make_shared<self_shared>(313);
	sp->print();
//不能对一个普通对象(非shared_ptr管理的对象)使用shared_from_this()获取share_ptr
	auto p = sp->shared_from_this();
	p->x = 1000;
	sp->print();
}
