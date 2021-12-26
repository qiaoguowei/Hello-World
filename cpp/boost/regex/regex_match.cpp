#include <iostream>
#include <boost/regex.hpp>

using namespace std;

void m_regex_match()
{
	boost::regex re("(?:[a-z0-9-]+)://");
	boost::cmatch what;
	if(!boost::regex_match("https://", what, re))
	{
		cout << "regex_match failed." << endl;
		return ;
	}
	cout << what.size() << endl;
	cout << what[0] << endl;
	if(what[1].matched)
	{
		cout << what[1] << endl;
	}
	cout << "successful." << endl;
}

void test2()
{
	boost::regex re("(?:(?:([\\.a-z0-9-]+)\\.)?s3\\.([a-zA-Z0-9-]+)\\.amazonaws\\.com(?:\\.cn)?)");
	boost::cmatch what;
	std::string str1 = "my.bucket.s3.cn-north-1.amazonaws.com";
	if(!boost::regex_match(str1.c_str(), what, re))
	{
		std::cout << "regex_match failed." << std::endl;
		return ;
	}
	cout << what.size() << endl;
	for(int i = 0; i < what.size(); ++i)
	{
		cout << what[i] << endl;
	}
}

int main()
{
	//m_regex_match();
	test2();

	return 0;
}














