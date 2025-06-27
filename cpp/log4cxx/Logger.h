#ifndef _LOGGER_H
#define _LOGGER_H

#include <log4cxx/logger.h>
#include <log4cxx/helpers/properties.h>
#include <string>

struct LoggerParameter
{
	LoggerParameter()
	{   
		module_tag = "OWN";
		level = "TRACE";
		console_flag = true;
		file_flag = true;
		file_path = "/home/qgw/log/own";
		file_size = "1024000";
		file_backup = "4";
		syslog_flag = true;
		syslog_ip = "127.0.0.1";
	}   
	std::string module_tag;
	std::string level;
	bool console_flag;
	bool file_flag;
	std::string file_path;
	std::string file_size;
	std::string file_backup;
	bool syslog_flag;
	std::string syslog_ip;
};

class Logger
{
private:
	static log4cxx::LoggerPtr sLogger;
	static log4cxx::LoggerPtr cfgLogger;
	static log4cxx::LoggerPtr diagLogger;
};




#endif


