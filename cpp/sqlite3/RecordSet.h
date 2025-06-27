#ifndef _RECORDSET_H
#define _RECORDSET_H

#include <iostream>
#include <string>

using namespace std;

typedef struct st_simple_field
{
	string name;
}SIMPLE_FIELD;

typedef struct st_simple_record
{
	string *values;
}SIMPLE_RECORD;

class RecordSet
{
public:
	RecordSet();
	virtual ~RecordSet();

	SIMPLE_FIELD *getField(int aFieldId);
	SIMPLE_FIELD *getField(const char *aFieldName);
	std::string getValue(int aRowId, int aFieldId);
	std::string getValue(int aRowId, const char *aFieldName);
	int getNumberOfRecords();
	int getNumberOfFields();
	void setFieldArray(SIMPLE_FIELD *aFieldArray, int aLength);
	void setRecordArray(SIMPLE_RECORD *aRecordArray, int aLength);
private:
	void clearFieldArray();
	void clearRecordArray();
	int getNumberOfFieldByName(const char *aName);
private:
	SIMPLE_FIELD *m_pFieldArray;
	SIMPLE_RECORD *m_pRecordArray;
	unsigned long m_Cursor;
	int m_NumberOfRecords;
	int m_NumberOfFields;
};



#endif







