#include "SequenceList.h"
#include <iostream>


void SequenceList::Initiate()
{
    len = 0;
}

int SequenceList::Insert(DataType x, int i)
{
    int j;
    if (len >= MAXSIZE)
    {
        std::cout << "overflow!" << std::endl;
        return 0;
    }
    else if ((i < 1) || (i > len + 1))
    {
        std::cout << "position is not correct!" << std::endl;
        return 0;
    }
    else
    {
        for (j = len; j >= i; j--)
        {
            data[j] = data[j - 1];
        }
        data[i - 1] = x;
        len++;

        return 1;
    }
}

int SequenceList::Deleted(int i)
{
    int j;
    if ((i < 1) || (i > len))
    {
        std::cout << "position is not correct!" << std::endl;
        return 0;
    }
    else
    {
        for (j = i; j < len; j++)
        {
            data[j - 1] = data[j];
        }
        len--;

        return 1;
    }
}

int SequenceList::Locate(DataType x)
{
    int j = 0;
    while ((j < len) && (data[j] != x))
        j++;

    if (j < len)
        return j + 1;
    else
        return 0;
}








