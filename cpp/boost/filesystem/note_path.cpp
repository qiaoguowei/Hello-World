class path
{
public:
	typedef char_or_wchar_t value_type;		//路径的字符类型
	typedef std::basic_string<value_type> string_type;	//路径使用的字符串类型
	constexpr value_type preferred_separator;	//路径的分隔符

	path();
	path(const path& p);
	path(Source const& source);
	path(InputIerator begin, InputIerator end);

	path& operator=(const path& p);
	path& operator=(Source const& source);

};
