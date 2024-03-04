#ifndef _SQLITECONNECTIONPOOL_H
#define _SQLITECONNECTIONPOOL_H

#include <list>
#include <string>
#include "SqliteConnection.h"
#include <boost/thread/mutex.hpp>

class SqliteConnectionPool
{
public:
	SqliteConnectionPool(int maxSize);
	~SqliteConnectionPool();

	void initConnection(int iInitialSize);
	void destoryConnPool();
	SqliteConnection *getConnection();
	void releaseConnection(SqliteConnection *conn);
	void checkDbPoolActive();
	void setDbName(std::string dbname);
	void setMaxPoolSize(int maxsize);

private:
	void destoryConnection(SqliteConnection *conn);
	SqliteConnection *createConnection();

private:
	int m_curSize;
	int m_maxSize;

	string m_dbname;
	list<SqliteConnection *> m_connList;

	boost::mutex m_mutex;
};




#endif







