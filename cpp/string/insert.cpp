#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//string& insert (size_t pos, size_t n, char c);
int main()
{
    string clearSql = "delete from CacheRecord_";
    const size_t indexPos = clearSql.find("_") + 1;

    std::stringstream indexToStr;
    indexToStr << 12;
    clearSql.insert(indexPos, indexToStr.str().size(), ' ');
    clearSql += " where match_time<10000";

    cout << clearSql << endl;

    string index = "12";
    clearSql.replace(indexPos, index.size(), index);
    cout << clearSql << endl;
}
