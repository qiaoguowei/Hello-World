#include <cstring>
#include "RecordSet.h"

using namespace std;


RecordSet::RecordSet() 
	: m_pFieldArray(NULL), m_pRecordArray(NULL), m_Cursor(-1), m_NumberOfRecords(0), m_NumberOfFields(0)
{
}

RecordSet::~RecordSet()
{
	clearFieldArray();
	clearRecordArray();
}

SIMPLE_FIELD *RecordSet::getField(int aFieldId)
{
	if (aFieldId < 0 || aFieldId >= m_NumberOfFields)
	{
		return NULL;
	}
	return &m_pFieldArray[aFieldId];
}

SIMPLE_FIELD *RecordSet::getField(const char *aFieldName)
{
	return getField(getNumberOfFieldByName(aFieldName));
}

std::string RecordSet::getValue(int aRowId, int aFieldId)
{
	if (aRowId < 0 || aRowId >= m_NumberOfRecords || 
		aFieldId < 0 || aFieldId >= m_NumberOfFields || m_pRecordArray == NULL)
	{
		return "";
	}
	if (m_pRecordArray[aRowId].values == NULL)
	{
		return "";
	}
	return m_pRecordArray[aRowId].values[aFieldId];
}

std::string RecordSet::getValue(int aRowId, const char *aFieldName)
{
	return getValue(aRowId, getNumberOfFieldByName(aFieldName));
}

int RecordSet::getNumberOfRecords()
{
	return m_NumberOfRecords;
}

int RecordSet::getNumberOfFields()
{
	return m_NumberOfFields;
}

void RecordSet::setFieldArray(SIMPLE_FIELD *aFieldArray, int aLength)
{
	clearFieldArray();
	m_NumberOfFields = aLength;
	m_pFieldArray = aFieldArray;
}

void RecordSet::setRecordArray(SIMPLE_RECORD *aRecordArray, int aLength)
{
	clearRecordArray();
	m_NumberOfRecords = aLength;
	m_pRecordArray = aRecordArray;
}

void RecordSet::clearFieldArray()
{
	if (m_pFieldArray != NULL)
	{
		delete [] m_pFieldArray;
		m_pFieldArray = NULL;
	}
	m_NumberOfFields = 0;
}

void RecordSet::clearRecordArray()
{
	if (m_pRecordArray != NULL)
	{
		for (int i = 0; i < m_NumberOfRecords; ++i)
		{
			if (m_pRecordArray[i].values != NULL)
			{
				delete [] m_pRecordArray[i].values;
				m_pRecordArray[i].values = NULL;
			}
		}
		delete [] m_pRecordArray;
		m_pRecordArray = NULL;
	}
	m_NumberOfRecords = 0;
}

int RecordSet::getNumberOfFieldByName(const char *aName)
{
	int pos = -1;
	if (aName == NULL)
	{
		return pos;
	}
	for (int i = 0; i < m_NumberOfFields; ++i)
	{
		if (m_pFieldArray == NULL)
		{
			break;
		}
		else if (strcmp(m_pFieldArray[i].name.c_str(), aName) == 0)
		{
			pos = i;
			break;
		}
	}
	return pos;
}



