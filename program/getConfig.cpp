#include <iostream>
#include <fstream>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/scope_exit.hpp>
#include <map>
#include <string>

class Config
{
public:
	Config(std::string file_path);
	~Config();
	std::map<std::string, std::string> getConfig();
	template<typename T>
	T getValue(std::string& key);
	template<typename T>
	bool setValue(std::string& key, T value);
	bool save();
private:
	boost::property_tree::ptree m_config;
	std::string mFilename;
};

Config::Config(std::string file_path)
{
	this->mFilename = file_path;
	boost::filesystem::path m_path(file_path);
	if(boost::filesystem::exists(m_path))
	{
		boost::property_tree::read_xml(file_path, this->m_config);
	}
}

Config::~Config()
{
}

std::map<std::string, std::string> Config::getConfig()
{
	//return std::map<std::string, std::string>();
	std::map<std::string, std::string> map_config;
	boost::property_tree::ptree tree_config;

	try
	{
		tree_config = this->m_config.get_child("lms");
		BOOST_FOREACH(boost::property_tree::ptree::value_type v1, tree_config)
		{
			std::string key1("lms.");
			std::string key_postfix(v1.first.begin(), v1.first.end());
			key1 += key_postfix;

			boost::property_tree::ptree tree_config2 = this->m_config.get_child(key1);
			BOOST_FOREACH(boost::property_tree::ptree::value_type v2, tree_config2)
			{
				std::string key2(v2.first.begin(), v2.first.end());
				std::string value(v2.second.data().begin(), v2.second.data().end());
				std::string key = key1;
				key += ".";
				key += key2;
				map_config[key] = value;
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
T Config::getValue(std::string& key)
{
	T value;
	boost::property_tree::ptree child_ptree = m_config.get_child(key);
	value = child_ptree.get_value<T>();
	return std::move(value);
}

template<typename T>
bool Config::setValue(std::string& key, T value)
{
	boost::property_tree::ptree child_ptree = m_config.get_child(key);
	child_ptree.put_value<T>(value);
	return true;
}

bool Config::save()
{
	boost::filesystem::path destfile(this->mFilename);

	boost::filesystem::path tempfile = destfile.parent_path() / boost::filesystem::unique_path();
	std::ofstream ofs(tempfile.string(), std::ofstream::out);
	ofs.imbue(std::locale("en_US.UTF-8"));

	boost::property_tree::xml_writer_settings<std::string> settings(' ', 4);
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

int main()
{
	Config cc("/home/qgw/my_github/Hello-World/program/lms_local.xml");
	std::string str1 = "lms.app.manager_ip";
	std::string str2 = cc.getValue<std::string>(str1);
	std::cout << str2 << std::endl;
	//std::map<std::string, std::string> map_config = cc.getConfig();
	//for(auto x : map_config)
	//{
	//	std::cout << x.first << ", " << x.second << std::endl;
	//}
	cc.setValue<std::string>(str1, "1.1.1.1");
	//std::string str3 = cc.getValue<std::string>(str1);
	//std::cout << str3 << std::endl;
	cc.save();
}









