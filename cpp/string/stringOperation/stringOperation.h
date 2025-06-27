#ifndef _STRINGOPERATION_H
#define _STRINGOPERATION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class StringOperation
{
public:
	StringOperation() = default;
	~StringOperation() = default;
	static void stringSplit(const std::string& str, 
							const std::string& delimiters, 
							std::vector<std::string>& tokens);
	static int stringToTime(const std::string& strDataStr, time_t& timeData);
};

void StringOperation::stringSplit(const std::string& str,
								  const std::string& delimiters,
								  std::vector<std::string>& tokens)
{
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

int StringOperatioin::stringToTime(const std::string& strDataStr, time_t& timeData)
{
	char *pBeginPos = (char *)strDateStr.c_str();
	char *pPos = strstr(pBeginPos, "-");
	if (pPos == NULL)
	{
		return -1;
	}

	int iYear = atoi(pBeginPos);
	int iMonth = atoi(pPos + 1);
	pPos = strstr(pPos + 1, "-");
	if (pPos == NULL)
	{
		return -1;
	}
	int iDay = atoi(pPos + 1);
	int iHour = 0;
	int iMin = 0;
	int iSec = 0;
	pPos = strstr(pPos + 1, " ");
}


#endif









