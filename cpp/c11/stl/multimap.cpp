#include <iostream>
#include <map>
#include <string>

// multimap::lower_bound/upper_bound
int test1()
{
	std::multimap<char,int> mymultimap;
	std::multimap<char,int>::iterator it,itlow,itup;

	mymultimap.insert(std::make_pair('a',10));
//	mymultimap.insert(std::make_pair('b',121));
	mymultimap.insert(std::make_pair('c',1001));
//	mymultimap.insert(std::make_pair('c',2002));
	mymultimap.insert(std::make_pair('d',11011));
	mymultimap.insert(std::make_pair('e',44));

	itlow = mymultimap.lower_bound ('b');  // itlow points to b
	itup = mymultimap.upper_bound ('d');   // itup points to e (not d)

	// print range [itlow,itup):
	for (it=itlow; it!=itup; ++it)
		std::cout << (*it).first << " => " << (*it).second << '\n';
	std::cout << (*it).first << " => " << (*it).second << '\n';

	return 0;
}

 //multimap::emplace

int test2 ()
{
	std::multimap<std::string,float> mymultimap;

	mymultimap.emplace("apple",1.50);
	mymultimap.emplace("coffee",2.10);
	mymultimap.emplace("apple",1.40);

	std::cout << "mymultimap contains:";
	for (auto& x: mymultimap)
		std::cout << " [" << x.first << ':' << x.second << ']';
	std::cout << '\n';

	return 0;
}

// ==
int test3()
{
	std::multimap<int, std::string> mymultimap;

	if(mymultimap.upper_bound(1) == mymultimap.begin())
	{
		std::cout << "test3(), no problem." << std::endl;
	}
	return 0;
}

int main()
{
	test1();
	test2();
	test3();
}
