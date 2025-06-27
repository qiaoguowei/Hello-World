#ifndef __ADLIST_H
#define __ADLIST_H

typedef struct listNode
{
    struct listNode *prev;
    struct listNode *next;
    void *value;
}listNode;

typdef struct list
{
    listNode *head; //表头节点
    listNode *tail; //表尾节点
    unsigned long len;  //链表所包含的节点数量

    void (*dup)(void *ptr); //节点值复制函数

    void (*free)(void *ptr);    //节点值释放函数

    int (*match)(void *ptr, void *key)  //节点值对比函数
} list;

#endif

