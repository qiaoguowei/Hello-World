#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
namespace bf = boost::filesystem;

void test1()
{
	boost::filesystem::path p("/home/qgw/program/cplusplus/boost/filesystem/testDir");
	cout << p.string() << endl;
}

void test2()
{
	bf::path p("/home/qgw/program/cplusplus/boost/filesystem/file_size.cpp");
	auto base_name = p.filename(); //文件名
	cout << base_name.string() << endl;

	auto relative_subpath = base_name.replace_extension(); //去掉文件扩展名
	cout << relative_subpath.string() << endl;
}

void m_status()
{
	boost::filesystem::path p("/home/qgw/program/cplusplus/boost/filesystem/testDir");
	unsigned long permission = (unsigned)bf::status(p).permissions();
	cout << permission << endl;
}

void m_replace_extension()
{
	boost::filesystem::path p("/home/qgw/program/cplusplus/boost/filesystem/file_size.cpp.zip");
	auto base_name = p.filename();
	cout << base_name << endl;
	std::string suffix = base_name.extension().string();
	cout << suffix << endl;

	std::string name_without_extension = base_name.stem().string();
	cout << name_without_extension << endl;

	auto relative_subpath = base_name.replace_extension();
	cout << relative_subpath.string() << endl;
}

void m_stem()
{
	std::cout << boost::filesystem::path("/foo/bar.txt").stem() << '\n'; // outputs "bar"
	std::cout << boost::filesystem::path(".hidden").stem() << '\n';      // v3 outputs ""
	                                                  // v4 outputs ".hidden"
	std::cout << boost::filesystem::basename(boost::filesystem::path("/foo/ssss.txt")) << std::endl;
	std::cout << boost::filesystem::basename(boost::filesystem::path("/foo/ssss")) << std::endl;
	std::cout << boost::filesystem::basename(boost::filesystem::path("/foo/ssss.txt.cpp")) << std::endl;
	boost::filesystem::path p = "foo.bar.baz.tar";
	cout << p.string() << endl;
	for (; !p.extension().empty(); p = p.stem())
		std::cout << p.extension() << '\n';
}

int main()
{
    m_replace_extension();
	//m_stem();
    //test2();
}








