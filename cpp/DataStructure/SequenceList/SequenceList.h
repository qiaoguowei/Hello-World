#ifndef __SEQUENCELIST_H
#define __SEQUENCELIST_H

#define MAXSIZE 100
typedef int DataType;

class SequenceList
{
public:
    void Initiate();
    int Length();
    int Insert(DataType x, int i);
    int Deleted(int i);
    int Locate(DataType x);
    DataType Get(int i);

private:
    DataType data[MAXSIZE];
    int len;
};


#endif

