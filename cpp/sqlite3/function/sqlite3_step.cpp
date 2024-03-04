#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

int main()
{
    sqlite3 *mDBHandler = NULL;
    if (SQLITE_OK != sqlite3_open("./test.db", &mDBHandler))
    {
        cout << sqlite3_errmsg(mDBHandler) << endl;
        return -1;
    }
    
    sqlite3_stmt *stmt = NULL;
    string querySql = "select col_version from tbl_meta_info order by col_version ASC";
    int mRet = sqlite3_prepare_v2(mDBHandler, querySql.c_str(), -1, &stmt, NULL);
    if (mRet != SQLITE_OK)
    {
        cout << sqlite3_errmsg(mDBHandler) << endl;
        sqlite3_close(mDBHandler);
        return -1;
    }

    int count = sqlite3_column_count(stmt);
    if (count == 0)
    {
        sqlite3_finalize(stmt);
        sqlite3_close(mDBHandler);
        return -1;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int dbVersion = sqlite3_column_int(stmt, 0);
        cout << dbVersion << endl;
    }
    sqlite3_finalize(stmt);

    sqlite3_close(mDBHandler);

    return 0;

}








