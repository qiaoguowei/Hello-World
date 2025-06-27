#include <iostream>
#include <string>
#include <SqliteConnection.h>
#include <RecordSet.h>

using namespace std;

int main()
{
	SqliteConnection m_sql;
	m_sql.openDB("./m_name.db");
	m_sql.createTable("detail(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
	m_sql.execInsert("insert into detail (name) values('aaa')");
	m_sql.closeDB();
}
