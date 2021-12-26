#include <iostream>
#include <boost/format.hpp>
#include <string>
#include <sqlite3.h>
#include <boost/smart_ptr.hpp>

class SqlOperator
{
public:
	SqlOperator(std::string path) : m_db_path(path), m_db(NULL) {}
	bool init();
	bool startTransaction();
	bool endTransaction(bool commit);
	bool create_table();
	bool insert_table(std::string name);
	bool query_table(std::string& name);
	~SqlOperator();
private:
	std::string m_db_path;
	sqlite3 *m_db;
};

SqlOperator::~SqlOperator()
{
	std::cout << "~SqlOperator, destory." << std::endl;
	if(m_db != NULL)
	{
		sqlite3_close(m_db);
		m_db = NULL;
		std::cout << "~SqlOperator, m_db is closed." << std::endl;
	}
}

bool SqlOperator::init()
{
	std::cout << "SqlOperator, create db : " << m_db_path << std::endl;
	if(sqlite3_open_v2(m_db_path.c_str(), &m_db, \
				SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, NULL) != SQLITE_OK)
	{
		std::cout << "sqlite3_open failed." << std::endl;
		return false;
	}
	std::cout << "create db success." << std::endl;
	return true;
}

bool SqlOperator::startTransaction()
{
	char *err = NULL;
	int ret = 0;
	if(m_db == NULL)
	{
		std::cout << "m_db is NULL." << std::endl;
		return false;
	}

	if((ret = sqlite3_exec(m_db, "begin;", NULL, 0, &err)) != SQLITE_OK)
	{
		std::cout << "sqlite3_exec return " << ret << std::endl;
		if(err != NULL)
		{
			std::cout << "exec sql failed : " << err << std::endl;
			sqlite3_free(err);
		}
		return false;
	}
	return true;
}

bool SqlOperator::endTransaction(bool commit)
{
	char *err = NULL;
	int ret = 0;
	std::string sql;
	sql = commit ? "commit;" : "rollback;";
	if(m_db == NULL)
	{
		std::cout << "endTransactioin, m_db is null." << std::endl;
		return false;
	}

	if((ret = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err)) != SQLITE_OK)
	{
		std::cout << "endTransactioin, sqlite3_exec return : " << ret << std::endl;
		if(err != NULL)
		{
			std::cout << "endTransactioin, exec sql failed : " << err << std::endl;
			sqlite3_free(err);
		}
		return false;
	}
	return true;
}

bool SqlOperator::create_table()
{
	std::string sql = "create table if not exists detail";
	sql += "(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)";
	char *err;
	if(m_db == NULL)
	{
		std::cout << "create_table, m_db is null." << std::endl;
		return false;
	}

	int ret = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err);
	if(ret != SQLITE_OK)
	{
		std::cout << "create_table, sqlite3_exec return : " << ret << std::endl;
		if(err != NULL)
		{
			std::cout << "create_table, sqlite3_exec failed : " << err << std::endl;
			sqlite3_free(err);
		}
		return false;
	}
	return true;
}

bool SqlOperator::insert_table(std::string name)
{
	auto fmt = boost::format("insert into detail (id, name) values(null, '%s')") % name;
	std::string sql = fmt.str();
	char *err;
	if(m_db == NULL)
	{
		std::cout << "insert_table, m_db is null." << std::endl;
		return false;
	}

	if(!startTransaction())
	{
		std::cout << "insert_table, startTransaction failed." << std::endl;
		return false;
	}

	int ret = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err);

	if(ret != SQLITE_OK)
	{
		endTransaction(false);
		std::cout << "insert_table, sqlite3_exec return : " << ret << std::endl;
		if(err != NULL)
		{
			std::cout << "insert_table, sqlite3_exec failed : " << err << std::endl;
			sqlite3_free(err);
		}
		return false;
	}
	else
	{
		endTransaction(true);
		std::cout << "insert_table, insert success." << std::endl;
	}
	return true;
}

bool SqlOperator::query_table(std::string& name)
{
	std::cout << "query_table, begin." << std::endl;
	std::string sql = "select name from detail";
	char *err = NULL;
	char **result = NULL;
	int row_num = 0;
	int col_num = 0;
	int index = 0;
	bool re = true;

	if(m_db == NULL)
	{
		std::cout << "query_table, m_db is null." << std::endl;
		return false;
	}

	int ret = sqlite3_get_table(m_db, sql.c_str(), &result, &row_num, &col_num, &err);
	if(ret != SQLITE_OK)
	{
		std::cout << "query_table, sqlite3_get_table return : " << ret << std::endl;
		re = false;
		goto END;
	}
	else
	{
		std::cout << "row_num = " << row_num << ", col_num = " << col_num << std::endl;
		index = col_num;//sqlite3_get_table result里面的前col_num存的是字段名称
		for(int i = 0; i < row_num; i++)
		{
			if(i == 2)//取表中的第二条记录
				break;
			for(int j = 0; j < col_num; j++)
			{
				if(j == 0)
					name = result[index++];
			}
		}
	}
END:
	if(err != NULL)
	{
		std::cout << "query_table, err_msg : " << err << std::endl;
		sqlite3_free(err);
	}
	if(result != NULL)
	{
		sqlite3_free_table(result);
	}

	return re;
}

int main(int argc, char *argv[])
{
	boost::shared_ptr<SqlOperator> so(new SqlOperator("/home/qgw/program/cplusplus/sqlite3/m_name.db"));
	if(!so->init())
		return -1;
	if(!so->create_table())
		return -1;
	if(argc == 2)
	{
		if(!so->insert_table(argv[1]))
			return -1;
	}
	std::string str1;
	if(!so->query_table(str1))
		return -1;
	std::cout << "query_table, return : " << str1 << std::endl;


	return 0;
}




















