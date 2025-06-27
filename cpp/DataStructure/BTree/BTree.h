#ifndef __BTREE_H
#define __BTREE_H

#include <string>

struct BTreeNode
{
    int keyNum;                 //节点当前关键字个数
    int keyword[m + 1];         //关键字数组，keyword[0]未用
    BTreeNode *parent;          //双亲结点指针
    BTreeNode *kids[m + 1];     //孩子结点指针数组
    std::string *recptr[m + 1];

    BTreeNode()
    {
        keyNum = 0;
        parent = NULL;
        for (int i = 0; i < m + 1; i++)
        {
            kids[i] = NULL;
        }
    }
};

struct FoundResult          //B树的查找结果类型
{
    BTreeNode *btn;         //指向找到的结点
    int i;                  //1<=i<=m,在结点中的关键字位序
    int tag;                //1：查找成功，0：查找失败

};


#endif

