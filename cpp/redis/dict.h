#ifndef __DICT_H
#define __DICT_H

typedef struct dictht
{
    dictEntry **table;  //哈希表数组
    unsigned long size; //哈希表大小
    unsigned long sizemask; //哈希表大小掩码，用于计算索引值，总是等于size-1
    unsigned long used; //该哈希表已有节点的数量
}dictht;

typedef struct dictEntry
{
    void *key;

    union
    {
        void *val;
        uint64_t u64;
        int64_t s64;
    } v;

    struct dictEntry *next; //指向下个哈希表节点，形成链表
} dictEntry;

typedef struct dict
{
    dictType *type; //类型特定函数
    void *privdata;
    dictht ht[2];   //哈希表
    int rehashidx;  //rehash索引，不再进行时，值为-1
}dict;

#endif


