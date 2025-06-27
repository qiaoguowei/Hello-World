#include <iostream>
#include <sstream>
#include <fstream>
//#include <boost/spirit.hpp>
#include <boost/spirit/include/classic.hpp>

using namespace std;

struct json_grammar : public boost::spirit::classic::grammar<json_grammar>
{
	struct print
	{
		void operator()(const char* begin, const char* end) const
		{
			cout << std::string(begin, end) << endl;
		}

		void operator()(const double d) const
		{
			cout << d << endl;
		}
	};

	template <typename Scanner>
	struct definition
	{
		boost::spirit::classic::rule<Scanner> object, member, string, value, number, array;

		definition(const json_grammar& self)
		{
			using namespace boost::spirit::classic;
			//boost::spirit::ch_p 可用于创建一个针对单个字符的分析器，相当于将字符置于双引号中
			object = "{" >> member >> *("," >> member) >> "}"; 
			member = string[print()] >> ":" >> value; 
			string = "\"" >> *~ch_p("\"") >> "\""; 
			value = string | number | object | array | str_p("true")[print()] | "false" | "null"; 
			number = real_p[print()]; 
			array = "[" >> value >> *("," >> value) >> "]"; 
		}

		const boost::spirit::classic::rule<Scanner> &start() 
		{
			return object;
		}
	};
};

int main(int argc, char *argv[])
{
	std::ifstream fs(argv[1]); 
	std::ostringstream ss; 
	ss << fs.rdbuf(); 
	std::string data = ss.str(); 

	json_grammar g; 
	boost::spirit::classic::parse_info<> pi = \
		boost::spirit::classic::parse(data.c_str(), g, boost::spirit::classic::space_p); 
	if (pi.hit) //如果文本被成功分析，则属性 hit 被设置为 true
	{ 
		if (pi.full) //如果文本中的所有字符都被分析完了，最后没有剩余空格，则 full 也被设置为 true
			std::cout << "parsing all data successfully" << std::endl; 
		else //此时，可以访问属性 stop 来获得停止分析的文本位置
			std::cout << "parsing data partially" << std::endl; 
		std::cout << pi.length << " characters parsed" << std::endl; 
	} //仅当 hit 为 true 时，length 是有效的，其中保存了被成功分析的字符数量
	else 
		std::cout << "parsing failed; stopped at '" << pi.stop << "'" << std::endl; 
}











