#include <iostream>
#include <boost/thread/lock_guard.hpp>
#include <SqliteConnectionPool.h>

using namespace std;

#define DEFAULT_MAXSIZE 10

SqliteConnectionPool::SqliteConnectionPool(int maxSize)
{
	m_curSize = 0;
	m_maxSize = DEFAULT_MAXSIZE;
	if (maxSize > 0)
	{
		m_maxSize = maxSize;
	}
}

SqliteConnectionPool::~SqliteConnectionPool()
{
	this->destoryConnPool();
}

void SqliteConnectionPool::initConnection(int iInitialSize)
{
	SqliteConnection *conn;
	boost::lock_guard<boost::mutex> guard(m_mutex);
	if (iInitiaSize > m_maxSize)
	{
		m_maxSize = iInitiaSize;
	}

	for (int i = 0; i < iInitiaSize; ++i)
	{
		conn = this->createConnection();
		if (conn)
		{
			m_connList.push_back(conn);
			++this->m_curSize;
		}
		else
		{
			cout << "create connection failed!" << endl;
		}
	}
}
void SqliteConnectionPool::destoryConnPool()
{
	boost::lock_guard<boost::mutex> guard(m_mutex);
	SqliteConnection *conn = NULL;
	while (!m_connList.emptr())
	{
		con = m_connList.front();
		m_connList.pop_front();
		this->destoryConnection(con);
	}
}

SqliteConnection *SqliteConnectionPool::getConnection()
{
	SqliteConnection *con;
	boost::lock_guard<boost::mutex> guard(m_mutex);
	if (m_connList.size() > 0)
	{
		con = m_connList.front();
		m_connList.pop_front();
		if (con->isClosed())
		{
			delete con;
			con = this->createConnection();
		}
		if (con == NULL)
		{
			--m_curSize;
		}
		return con;
	}
	else
	{
		if (m_curSize < m_maxSize)
		{
			con = this->createConnection();
			if (con)
			{
				++m_curSize;
				return con;
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return NULL;
		}
	}
}

void SqliteConnectionPool::releaseConnection(SqliteConnection *conn)
{
	boost::lock_guard<boost::mutex> guard(m_mutex);
	if (conn)
	{
		m_connList.push_back(conn);
	}
}

void SqliteConnectionPool::checkDbPoolActive()
{
	boost::lock_guard<boost::mutex> guard(m_mutex);
	int nSize = m_connList.size();
	int n_NormalNum = 0;
	list<SqliteConnection *>::iterator iter = m_connList.begin();
	for (; iter != m_connList.end; )
	{
		int res;
		std::string zErrorMsg;
		bool bActive = true;
		SqliteConnection *conn = (*iter);
		if (conn)
			bActive = conn->isActive();
		if (!bActive)
		{
			destoryConnection(conn);
			iter = m_connList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	int nNum = nSize - m_connList.size();
	for (int i = 0; i < nNum; ++i)
	{
		SqliteConnection *conn;
		conn = this->createConnection();
		if (conn)
		{
			m_connList.push_back(conn);
		}
	}
}

void SqliteConnectionPool::setDbName(std::string dbname)
{
	m_dbname = dbname;
}

void SqliteConnectionPool::setMaxPoolSize(int maxsize)
{
	if (maxsize < m_curSize)
	{
		maxsize = m_curSize;
	}
	m_maxSize = maxsize;
}

void SqliteConnectionPool::destoryConnection(SqliteConnection *conn)
{
	if (conn)
	{
		conn->closeDB();
		delete conn;
		conn = NULL;
		--m_curSize;
	}
	return;
}

SqliteConnection *SqliteConnectionPool::createConnection()
{
	SqliteConnection *conn = new SqliteConnection();
	int res = conn->openDB(m_dbname.c_str());
	if (0 == res)
		return conn;
	delete conn;
	return NULL;
}
















