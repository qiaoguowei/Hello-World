#ifndef _SQLITECONNECTION_H
#define _SQLITECONNECTION_H

#include <sqlite3.h>
#include <iostream>
#include "RecordSet.h"

class SqliteConnection
{
public:
	SqliteConnection();
	virtual ~SqliteConnection();

	int openDB(const char *path);
	int closeDB();
	int createTable(const char *table_name_and_field);
	int createIndex(const char *sql_state);
	int dropTble(const char *table_name);
	int dropIndex(const char *index_name);
	RecordSet *execSelect(const char *select_state);
	int execInsert(const char *insert_state, bool bTransaction = false);
	int execDelete(const char *delete_state, bool bTransaction = false);
	int execUpdate(const char *update_state, bool bTransaction = false);

	bool isActive();
	bool isClosed();
	bool isTableExists(const char *table_name);
	bool isIndexExists(const char *index_name);

private:
	sqlite3 *sqlite_db_;
	bool is_close_;

	static int callBackFunc(void *not_used, int element_count, char **element, char **col_name);
};



#endif







