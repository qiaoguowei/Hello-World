#ifndef __SDS_H
#define __SDS_H

struct sdshdr
{
    int len;    //记录SDS所保存字符串的长度
    int free;   //记录buf数组中未使用字节的数量
    char *buf;  //字节数组，用于保存字符串
};


#endif

