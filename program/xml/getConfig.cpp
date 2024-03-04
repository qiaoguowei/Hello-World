#include <iostream>
#include <fstream>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/scope_exit.hpp>
#include <map>
#include <string>

using namespace std;

class Config
{
public:
	Config(std::string file_path);
	~Config();
	std::map<std::string, std::string> getConfig();
	template<typename T>
	T getValue(std::wstring& key);
	template<typename T>
	bool setValue(std::wstring& key, T value);
	bool save();
	bool isNodeExist(const string& nodePath);
private:
	boost::property_tree::wptree m_config;
	std::string mFilename;
};

std::wstring str2wstr(std::string str)
{
	std::wstring wstr(str.begin(), str.end());
	return wstr;
}

std::string wstr2str(std::wstring wstr)
{
	std::string str(wstr.begin(), wstr.end());
	return str;
}

Config::Config(std::string file_path)
{
	this->mFilename = file_path;
	std::wifstream ifs(file_path, std::ios::in);
	ifs.imbue(std::locale("en_US.UTF8"));
	boost::property_tree::read_xml(ifs, this->m_config, boost::property_tree::xml_parser::trim_whitespace);
}

Config::~Config()
{
}

std::map<std::string, std::string> Config::getConfig()
{
	//return std::map<std::string, std::string>();
	std::map<std::string, std::string> map_config;

	try
	{
		boost::property_tree::wptree &tree_config = this->m_config.get_child(L"lms");
		BOOST_FOREACH(boost::property_tree::wptree::value_type v1, tree_config)
		{
			std::wstring key1(L"lms.");
			std::wstring key_postfix(v1.first.begin(), v1.first.end());
			key1 += key_postfix;

			boost::property_tree::wptree tree_config2 = this->m_config.get_child(key1);
			BOOST_FOREACH(boost::property_tree::wptree::value_type v2, tree_config2)
			{
				std::wstring key2(v2.first.begin(), v2.first.end());
				std::wstring value(v2.second.data().begin(), v2.second.data().end());
				std::wstring key = key1;
				key += L".";
				key += key2;
				map_config[wstr2str(key)] = wstr2str(value);
			}
		}
	}
	catch(...)
	{
		std::cerr << "occur error." << std::endl;
	}
	return map_config;
}

template<typename T>
T Config::getValue(std::wstring& key)
{
	T value;
	boost::property_tree::wptree child_ptree = m_config.get_child(key);
	value = child_ptree.get_value<T>();
	return std::move(value);
}

template<typename T>
bool Config::setValue(std::wstring& key, T value)
{
	boost::property_tree::wptree &child_ptree = m_config.get_child(key);
	child_ptree.put_value<T>(value);
	return true;
}

bool Config::save()
{
	boost::filesystem::path destfile(this->mFilename);

	boost::filesystem::path tempfile = destfile.parent_path() / boost::filesystem::unique_path();
	std::wofstream ofs(tempfile.string(), std::ofstream::out);
	ofs.imbue(std::locale("en_US.UTF-8"));

	boost::property_tree::xml_writer_settings<std::wstring> settings(' ', 4);
	write_xml(ofs, m_config, settings);
	//write_xml(mFilename, m_config, settings);
	ofs.flush();
	bool isGood = ofs.good();
	ofs.close();

	BOOST_SCOPE_EXIT(&tempfile, &isGood)
	{
		if(!isGood)
		{
			boost::filesystem::remove(tempfile);
		}
		std::cout << tempfile.string() << std::endl;
	}BOOST_SCOPE_EXIT_END

	if(isGood)
	{
		boost::filesystem::rename(tempfile, destfile);
	}

	return isGood;
}

bool Config::isNodeExist(const string& nodePath)
{
	wstring nodeStr = str2wstr(nodePath);
	auto item = m_config.get_child_optional(nodeStr);
	if (item)
		return true;
	return false;
}

int main()
{
    Config cc("./ContentAnalysisEngine.xml");
    std::wstring str1 = L"ContentAnalysisEngine.components";

    for (auto 
    //if (cc.isNodeExist(wstr2str(str1)))
    //{
        //std::wstring str2 = cc.getValue<std::wstring>(str1);
        //std::cout << wstr2str(str2) << std::endl;
        //cout << "the node is exist." << endl;
    //}
    //else
    //{
    //    cout << "the node is not exist." << endl;
    //}
    //str1 += L".mode[name=\"block\"].TotalTimeout";
    //std::wstring str2 = cc.getValue<std::wstring>(str1);
    //std::cout << wstr2str(str2) << std::endl;

    //std::map<std::string, std::string> map_config = cc.getConfig();
    //for(auto x : map_config)
    //{
    //	std::cout << x.first << ", " << x.second << std::endl;
    //}
    //cc.setValue<std::wstring>(str1, L"127.0.0.1");
    //std::wstring str3 = cc.getValue<std::wstring>(str1);
    //std::wcout << str3 << std::endl;
    //cc.save();
}









