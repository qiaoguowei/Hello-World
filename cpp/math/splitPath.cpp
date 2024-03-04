#include <iostream>
#include <deque>
#include <set>
#include <string>
#include <cstring>
#include <jsoncpp/json/json.h>
#include <memory>
#include <sstream>
#include <unistd.h>

#include <assert.h>

using namespace std;

void subs2json(deque<string>& vstr, Json::Value& rdata, set<string>& dset, const string& md5);
bool search_value(const string& path, Json::Value& rdata, deque<string>& vstr, set<string>& dset, const string& md5);
void path_split(const string& dir, deque<string>& vstr)
{
	string ss(dir);
	string::size_type pos, prepos = 0;

	while ((pos = ss.find('/', prepos)) != string::npos) 
	{
		string s = ss.substr(0, pos);
		vstr.push_back(s);
		prepos = pos + 1;
	}
	if (!ss.substr(prepos).empty()) 
	{
		vstr.push_back(dir);
	}
}

void subs2json(deque<string>& vstr, Json::Value& rdata, set<string>& dset, const string& md5)
{
	Json::Value value;

	if (!vstr.empty())
	{
		string s = vstr.front();
		vstr.pop_front();
		if (!dset.count(s))
		{
			dset.insert(s);
			value["path"] = s;
			if (!vstr.empty())
			{
				value["dir"] = true;
				value["subs"] = Json::arrayValue;
				subs2json(vstr, value["subs"], dset, md5);
			} 
			else 
			{
				if (md5.empty()) 
				{
					value["dir"] = true;
					value["subs"] = Json::arrayValue;
				} 
				else 
				{
					value["dir"] = false;
					value["md5"] = md5;
				}   
			}   
			rdata.append(value);
		} 
		else 
		{
			search_value(s, rdata, vstr, dset, md5);
		}
	}
}

bool search_value(const string& path, 
				  Json::Value& rdata, 
				  deque<string>& vstr, 
				  set<string>& dset, 
				  const string& md5)
{
	assert(rdata.isArray());

	for (unsigned int i = 0; i < rdata.size(); i++) 
	{
		if (rdata[i].isObject()) 
		{
			if (!rdata[i]["dir"].asBool())
				continue;
			if (rdata[i]["path"].asString() == path) 
			{
				subs2json(vstr, rdata[i]["subs"], dset, md5);
				return true;
			} 
			else 
			{
				if (search_value(path, rdata[i]["subs"], vstr, dset, md5))
					return true;
			}
		}
	}

	return false;
}

int main()
{
	char buf[256];
	deque<string> vstr;
	set<string> dset;
	Json::Value root;
	ostringstream oss;
	Json::StreamWriterBuilder builder;
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	memset(buf, 0, sizeof(buf));
	getcwd(buf, sizeof(buf)-1);
	string filepath(buf);

	path_split(filepath, vstr);
	string md5 = "";
	root["data"] = Json::arrayValue;
	subs2json(vstr, root["data"], dset, md5);

	writer->write(root, &oss);
	cout << oss.str() << endl;
}








