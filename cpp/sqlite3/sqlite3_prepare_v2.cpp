#include <iostream>
#include <string>
#incluce <sqlite3.h>

using namespace std;

bool init(sqlite3 *_db, const string dbPath)
{
	if (_db != nullptr)
		return false;

	int rc = sqlite3_open(dbPath.c_str(), &_db);
	if (rc)
	{
		cout << "open db failed : " << sqlite3_errmsg(_db) << endl;
		sqlite3_close(_db);
		return false;
	}
}

bool select_operation();

int main()
{

}
