#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;

int main()
{
	boost::filesystem::path p("./clean.sh");
	boost::filesystem::path to_path("./bin/clean.sh");
	boost::filesystem::rename(p, to_path); //相当于shell的mv
}
