#ifndef _QIAO_HUFFMANTREE_H
#define _QIAO_HUFFMANTREE_H

typedef struct
{
    int weight;         //结点的权值
    int parent, lchild, rchild;     //结点的双亲，左孩子，右孩子的下标
}HTNode, *HuffmanTree;  //动态分配数组存储哈夫曼树

void createHuffmanTree(HuffmanTree &HT, int n);



#endif //_QIAO_HUFFMANTREE_H
