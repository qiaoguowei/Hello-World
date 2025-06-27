#include "HuffmanTree.h"

void createHuffmanTree(HuffmanTree &HT, int n)
{
    if (n <= 1)
        return ;

    m = 2 * n - 1;
    HT = new HTNode[m + 1]; //0号单元未用，所以需要动态分配m+1个单元，HT[m]表示根结点

    for (int i = 1; i <= m; ++i)
    {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }

    for (int i = 1; i <= n; ++i) //输入前n个单元中叶子结点的权值
        cin >> HT[i].weight;
    /*-------------------初始化工作结束，下面开始创建哈夫曼树-----------------*/
    for (int i = n + 1; i <= m; ++i)
    {
    }
}
