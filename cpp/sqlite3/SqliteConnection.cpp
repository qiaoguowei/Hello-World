#include <iostream>
#include <string.h>
#include "SqliteConnection.h"

using namespace std;


SqliteConnection::SqliteConnection()
{
	is_close_ = true;
}

SqliteConnection::~SqliteConnection()
{
	if (!is_close_)
		closeDB();
}

int SqliteConnection::openDB(const char *path)
{
	if (is_close_)
	{
		int res = sqlite3_open(path, &sqlite_db_);
		if (res != SQLITE_OK)
		{
			cout << "SqliteConnection, can't open database: " << sqlite3_errmsg(sqlite_db_) << endl;
			sqlite3_close(sqlite_db_);
			return -1;
		}
	}
	is_close_ = false;

	return 0;
}

int SqliteConnection::closeDB()
{
	if (!is_close_)
	{
		int res = sqlite3_close(sqlite_db_);
		if (res != SQLITE_OK)
		{
			cout << "SqliteConnection, can't close database: " << sqlite3_errmsg(sqlite_db_) << endl;
			return -1;
		}
	}
	is_close_ = true;

	return 0;
}

int SqliteConnection::createTable(const char *table_name_and_field)
{
	char *err_msg_ = 0;
	string create_table_state = "create table if not exists ";
	create_table_state += table_name_and_field;
	create_table_state += ";";
	int res = sqlite3_exec(sqlite_db_, create_table_state.c_str(), NULL, NULL, &err_msg_);
	if (res != SQLITE_OK)
	{
		cout << "SqliteConnection, create table failed: " << err_msg_ << endl;
		sqlite3_free(err_msg_);
		return -1;
	}

	return 0;
}

int SqliteConnection::createIndex(const char *sql_state)
{
	char *err_msg_ = 0;
	int res = sqlite3_exec(sqlite_db_, sql_state, NULL, NULL, &err_msg_);
	if (res != SQLITE_OK)
	{
		sqlite3_free(err_msg_);
		return -1;
	}

	return 0;
}

int SqliteConnection::dropTble(const char *table_name)
{
	char *err_msg_ = 0;
	string sql_state = "drop table ";
	sql_state += table_name;
	sql_state += ";";
	int res = sqlite3_exec(sqlite_db_, sql_state.c_str(), NULL, NULL, &err_msg_);
	if (res != SQLITE_OK)
	{
		cout << "SqliteConnection, drop table failed: " << err_msg_ << endl;
		sqlite3_free(err_msg_);
		return -1;
	}

	return 0;
}

int SqliteConnection::dropIndex(const char *index_name)
{
	char *err_msg_ = 0;
	string sql_state = "drop index ";
	sql_state += index_name;
	sql_state += ";";
	int res = sqlite3_exec(sqlite_db_, sql_state.c_str(), NULL, NULL, &err_msg_);
	if (res != SQLITE_OK)
	{
		sqlite3_free(err_msg_);
		return -1;
	}

	return 0;
}

RecordSet *SqliteConnection::execSelect(const char *select_state)
{
	char *err_msg_ = 0;
	char **pResult = 0;
	int rows;
	int fields;
	int index;
	int res;
	SIMPLE_FIELD *pField;
	SIMPLE_RECORD *pRow;
	RecordSet *recordset = new RecordSet;
	res = sqlite3_get_table(sqlite_db_, select_state, &pResult, &rows, &fields, &err_msg_);
	if (res != SQLITE_OK)
	{
		cout << "SqliteConnection, select operation failed: " << err_msg_ << endl;
		sqlite3_free(err_msg_);
		delete recordset;
		return NULL;
	}
	else
	{
		pField = new SIMPLE_FIELD[fields];
		pRow = new SIMPLE_RECORD[rows];
		if (pField == NULL || pRow == NULL || recordset == NULL)
		{
			if (pField != NULL)
				delete [] pField;
			if (pRow != NULL)
				delete [] pRow;
			if (recordset != NULL)
				delete recordset;
			sqlite3_free_table(pResult);
			return NULL;
		}
		for (int i = 0; i < fields; ++i)
		{
			pField[i].name = pResult[i];//将表的字段名保存到SIMPLE_FIELD
		}
	}
	recordset->setFieldArray(pField, fields);//将SIMPLE_FIELD保存到RecordSet类中

	index = fields;
	for (int i = 0; i < rows; ++i)
	{
		pRow[i].values = new string[fields];
		for (int j = 0; j < fields; ++j)
		{
			pRow[i].values[j] = pResult[index];//将查询出来的所有值保存到SIMPLE_RECORD
			++index;
		}
	}
	recordset->setRecordArray(pRow, rows);//将SIMPLE_RECORD保存到RecordSet类中
	sqlite3_free_table(pResult);
	return recordset;
}

int SqliteConnection::execInsert(const char *insert_state, bool bTransaction)
{
	char *err_msg_ = 0;
	int res;
	bool is_success = true;
	if (bTransaction)
	{
		res = sqlite3_exec(sqlite_db_, "begin;", NULL, NULL, &err_msg_);
		if (res != SQLITE_OK)
		{
			cout << "SqliteConnection, insert operation failed: " << err_msg_ << endl;
			sqlite3_free(err_msg_);
			return -1;
		}

		res = sqlite3_exec(sqlite_db_, insert_state, NULL, NULL, &err_msg_);
		if (res != SQLITE_OK)
		{
			cout << "SqliteConnection, insert operation failed: " << err_msg_ << endl;
			sqlite3_free(err_msg_);
			is_success = false;
		}
		if (is_success)
		{
			sqlite3_exec(sqlite_db_, "commit;", NULL, NULL, &err_msg_);
		}
		else
		{
			cout << "SqliteConnection, insert operation failed: " << err_msg_ << endl;
			sqlite3_exec(sqlite_db_, "rollback;", NULL, NULL, &err_msg_);
			return -1;
		}
	}
	else
	{
		res = sqlite3_exec(sqlite_db_, insert_state, NULL, NULL, &err_msg_);
		if (res != SQLITE_OK)
		{
			cout << "SqliteConnection, insert operation failed: " << err_msg_ << endl;
			sqlite3_free(err_msg_);
			return -1;
		}
	}
	return 0;
}

int SqliteConnection::execDelete(const char *delete_state, bool bTransaction)
{
	char *err_msg_ = 0;
	int res;
	bool is_success = true;
	if (bTransaction)
	{
		res = sqlite3_exec(sqlite_db_, "begin;", NULL, NULL, &err_msg_);
		if (res != SQLITE_OK)
		{
			cout << "SqliteConnection, delete operation failed: " << err_msg_ << endl;
			sqlite3_free(err_msg_);
			return -1;
		}

		res = sqlite3_exec(sqlite_db_, delete_state, NULL, NULL, &err_msg_);
		if (res != SQLITE_OK)
		{
			cout << "SqliteConnection, delete operation failed: " << err_msg_ << endl;
			sqlite3_free(err_msg_);
			is_success = false;
		}
		if (is_success)
		{
			sqlite3_exec(sqlite_db_, "commit;", NULL, NULL, &err_msg_);
		}
		else
		{
			cout << "SqliteConnection, delete operation failed: " << err_msg_ << endl;
			sqlite3_exec(sqlite_db_, "rollback;", NULL, NULL, &err_msg_);
			return -1;
		}
	}
	else
	{
		res = sqlite3_exec(sqlite_db_, delete_state, NULL, NULL, &err_msg_);
		if (res != SQLITE_OK)
		{
			cout << "SqliteConnection, delete operation failed: " << err_msg_ << endl;
			sqlite3_free(err_msg_);
			return -1;
		}
	}
	return 0;
}

int SqliteConnection::execUpdate(const char *update_state, bool bTransaction)
{
	char *err_msg_ = 0;
	int res;
	bool is_success = true;
	if (bTransaction)
	{
		res = sqlite3_exec(sqlite_db_, "begin;", NULL, NULL, &err_msg_);
		if (res != SQLITE_OK)
		{
			cout << "SqliteConnection, update operation failed: " << err_msg_ << endl;
			sqlite3_free(err_msg_);
			return -1;
		}

		res = sqlite3_exec(sqlite_db_, update_state, NULL, NULL, &err_msg_);
		if (res != SQLITE_OK)
		{
			cout << "SqliteConnection, update operation failed: " << err_msg_ << endl;
			sqlite3_free(err_msg_);
			is_success = false;
		}
		if (is_success)
		{
			sqlite3_exec(sqlite_db_, "commit;", NULL, NULL, &err_msg_);
		}
		else
		{
			cout << "SqliteConnection, update operation failed: " << err_msg_ << endl;
			sqlite3_exec(sqlite_db_, "rollback;", NULL, NULL, &err_msg_);
			return -1;
		}
	}
	else
	{
		res = sqlite3_exec(sqlite_db_, update_state, NULL, NULL, &err_msg_);
		if (res != SQLITE_OK)
		{
			cout << "SqliteConnection, update operation failed: " << err_msg_ << endl;
			sqlite3_free(err_msg_);
			return -1;
		}
	}
	return 0;
}

int SqliteConnection::callBackFunc(void *not_used, int element_count, char **element, char **col_name)
{
	for (int index = 0; index < element_count; ++index)
	{
		cout << col_name[index] << " = " << (element[index] ? element[index] : "NULL") << ", ";
	}
	cout << endl;
	return 0;
}

bool SqliteConnection::isActive()
{
	char *err_msg_ = 0;
	int res;
	//char *zErrorMsg;
	res = sqlite3_exec(sqlite_db_, "select 1;", NULL, NULL, &err_msg_);
	if (res != SQLITE_OK)
	{
		sqlite3_free(err_msg_);
		return false;
	}
	return true;
}

bool SqliteConnection::isClosed()
{
	return is_close_;
}

bool SqliteConnection::isTableExists(const char *table_name)
{
	int res;
	std::string querySql = "select count(*) from sqlite_master where type='table' and name='";
	querySql += table_name;
	querySql += "';";
	sqlite3_stmt *stmt = NULL;
	res = sqlite3_prepare_v2(sqlite_db_, querySql.c_str(), -1, &stmt, 0);
	if (res == SQLITE_OK)
	{
		sqlite3_step(stmt);
		int count = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);
		if (count > 0)
		{
			return true;
		}
	}
	return false;
}

bool SqliteConnection::isIndexExists(const char *index_name)
{
	int res;
	std::string querySql = "select count(*) from sqlite_master where type='index' and name='";
	querySql += index_name;
	querySql += "';";
	sqlite3_stmt *stmt = NULL;
	res = sqlite3_prepare_v2(sqlite_db_, querySql.c_str(), -1, &stmt, 0);
	if (res == SQLITE_OK)
	{
		sqlite3_step(stmt);
		int count = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);
		if (count > 0)
		{
			return true;
		}
	}
	return false;
}













