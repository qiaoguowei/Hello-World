#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>

namespace bf = boost::filesystem;

std::vector<bf::path> find_files(const bf::path &dir)
{
	std::vector<bf::path> v;
	if(!bf::exists(dir) || !is_directory(dir))
	{
		return v;
	}

	bf::recursive_directory_iterator end;
	for(bf::recursive_directory_iterator pos(dir); pos != end; ++pos)
	{
		if(!bf::is_directory(*pos))
		{
			v.push_back(pos->path());
		}
	}
	return v;
}

size_t copy_files(const bf::path &from_dir, const bf::path &to_dir)
{
	auto v = find_files(from_dir);
	if(v.empty())
	{
		return 0;
	}

	for(auto &p : v)
	{
		bf::path tmp = to_dir / p.string().substr(from_dir.parent_path().string().length());
		if(!bf::exists(tmp.parent_path()))
		{
			bf::create_directories(tmp.parent_path());
		}
		bf::copy_file(p, tmp);
	}
	return v.size();
}

int main()
{
	bf::path need_scan_dir("/home/qgw/my_github/Hello-World/program");
	bf::path to_dir("/home/qgw/my_github/Hello-World/program/FileOperator/testDir");
	int ret = copy_files(need_scan_dir, to_dir);
	std::cout << ret << std::endl;
}





