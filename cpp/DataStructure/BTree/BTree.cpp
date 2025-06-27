#include "BTree.h"
#include <iostream>


int Search(BTreeNode *head, int needFindKeyword)  //在p->keyword[1..p->keyNum]找k
{
    int i = 1;
    while (i <= head->keyNum && needFindKeyword > p->keyword[i])
        i++;
    return i;
}

void SearchBTree(BTreeNode *head, int needFindKeyword, FoundResult& result)
{
    int i = 0, found = 0;
    BTreeNode *tmpNode = head;
    BTreeNode *parentNode = NULL;//初始，tmpNode指向根节点，head将用于指向待查找结点，q指向其双亲
    while (tmpNode != NULL && 0 == found)
    {
        i = Search(tmpNode, needFindKeyword);
        if (i <= tmpNode->keyNum && tmpNode->key[i] == k)
            found = 1;
        else //指针下移
        {
            parentNode = tmpNode;
            tmpNode = tmpNode->kids[i - 1];
        }
    }

    if (1 == found) //查找成功，返回needFindKeyword的位置tmpNode及i
    {
        result = {tmpNode, i, 1 };
    }
    else            //查找不成功，返回needFindKeyword的插入位置parentNode及i
    {
        result = {parentNode, i, 0 };
    }
}

//将needSplitNode结点分裂成两个结点，前一半保留在原结点，后一半移入newNode所指新结点
void split(BTreeNode *needSplitNode, int subscript, BTreeNode *newNode) 
{
    int i, j;
    int needSplitNodeKeyNum = needSplitNode->keyNum;
    newNode = new BTreeNode();//生成新结点
    newNode->kids[0] = needSplitNode->kids[subscript];
    for (i = subscript + 1, j = 1; i <= needSplitNodeKeyNum; i++, j++)     //后一半移入newNode结点
    {
        newNode->keyword[j] = needSplitNode->keyword[i];
        newNode->kids[j] = needSplitNode->kids[i];
    }

    newNode->keyNum = needSplitNodeKeyNum - subscript;
    newNode->parent = needSplitNode->parent;
    for (i = 0; i <= needSplitNodeKeyNum - subscript; i++)
        if (newNode->kids[i] != NULL)
            newNode->kids[i]->parent = newNode;
    needSplitNode->keyNum = subscript - 1;
}


void newRoot(BTreeNode *newRoot, BTreeNode *oldRoot1, int newKeyword, BTreeNode *oldRoot2) //生成新的根结点
{
    newRoot = new BTreeNode();
    newRoot->keyNum = 1;
    newRoot->kids[0] = oldRoot1;
    newRoot->kids[1] = oldRoot2;
    newRoot->keyword[1] = newKeyword;
    if (oldRoot1 != NULL)
        oldRoot1->parent = newRoot;
    if (oldRoot2 != NULL)
        oldRoot2->parent = newRoot;
    newRoot->parent = NULL;
}

//关键字newKeyword和新结点指针newNode分别插到parentNode->keyword[subscript]和parentNode->kids[subscript]
void Insert(BTreeNode *parentNode, int subscript, int newKeyword, BTreeNode *newNode) 
{
    int j;
    int parentNodeKeyNum = parentNode->keyNum;
    for (j = parentNodeKeyNum; j >= subscript; j--)
    {
        parentNode->keyword[j + 1] = parentNode->keyword[j];
        parentNode->kids[j + 1] = parentNode->kids[j];
    }
    
    parentNode->keyword[i] = newKeyword;
    parentNode->kids[i] = newNode;
    if (newNode != NULL)
        newNode->parent = parentNode;
    parentNode->keyNum++;
}

void InsertBTree(BTreeNode *rootNode, int newKeyword, BTreeNode *parentNode, int subscript) 
{
    //在B树中q结点的key[i-1]和key[i]之间插入关键字k
    //若插入后结点关键字个数等于b树的阶，则沿着双亲指针链进行结点分裂，使得t仍是m阶B树
    int keyword;
    int newSubscipt;
    int finished = 0, needNewRoot = 0;
    BTreeNode *newNode;
    if (NULL == parentNode)
        newRoot(rootNode, NULL, newKeyword, NULL);
    else 
    {
        keyword = newKeyword; 
        newNode = NULL;
        while (0 == needNewRoot && 0 == finished) 
        {
            //keyword和newNode分别插到parentNode->keyword[subscript]和parentNode->kids[subscript]
            Insert(parentNode, subcript, keyword, newNode);
            if (parentNode->keyNum < m) 
                finished = 1;//插入完成
            else 
            {
                newSubscript = (m + 1) / 2; 
                split(parentNode, newSubscript, newNode); 
                keyword = parentNode->keyword[newSubscript];
                if (parentNode->parent != NULL) 
                {
                    parentNode = parentNode->parent; 
                    subscript = Search(parentNode, keyword);//在双亲结点中查找x的插入位置
                }
                else 
                    needNewRoot = 1;
            }
        }
        if (1 == needNewRoot)//rootNode是空树或者根结点已经分裂成为parentNode和newNode结点
            newRoot(rootNode, parentNode, keyword, newNode);
    }
}


void Remove(BTreeNode *mNode, int subscript)
{
    int j;
    int mNodeKeyNum = mNode->keyNum;
    for (j = subscript; j < mNodeKeyNum; j++) {
        mNode->keyword[j] = mNode->keyword[j + 1];
        mNode->kids[j] = mNode->kids[j + 1];
    }
    p->keyNum--;
}

void ReplaceWithKid(BTree& mNode, int subscript) //由后继最下层非终端结点的最小关键字代替结点中关键字key[i]
{
    BTreeNode *kidNode = mNode->kids[subscript];
    while (kidNode->kids[0] != NULL) 
        kidNode = kidNode->kids[0];
    mNode->keyword[subscript] = kidNode->keyword[1];
    mNode = kidNode;
}


void Restore(BTreeNode *mNode, int i, BTreeNode *tmpNode) //对B树进行调整
{
    int j;
    BTreeNode *parentNode = mNode->parent;
    if (parentNode == NULL) //若调整后出现空的根结点，则删除该根结点，树高减1
    {
        tmpNode = mNode; //根结点下移
        mNode = mNode->parent;
        return;
    }
    BTreeNode *lc;
    BTreeNode *rc;
    BTreeNode *pr;
    int finished = 0;
    int parentNodeSubscript = 0;
    while (!finished)
    {
        parentNodeSubscript = 0;
        while (parentNode->kids[parentNodeSubscript] != mNode) 
            parentNodeSubscript++; //确定mNode在parentNode子树中的位置
        if (parentNodeSubscript == 0)
        {
            parentNodeSubscript++;
            lc = NULL;
            rc = parentNode->kids[parentNodeSubscript];
        }
        else if (parentNodeSubscript == parentNode->keyNum)
        {
            rc = NULL; 
            lc = parentNode->kids[parentNodeSubscript - 1];
        }
        else
        {
            lc = parentNode->kids[parentNodeSubscript - 1]; 
            rc = parentNode->kids[parentNodeSubscript + 1];
        }

        if (parentNodeSubscript > 0 && lc != NULL && (lc->keyNum > (m - 1) / 2))//向左兄弟借关键字
        {
            mNode->keyNum++;
            for (j = mNode->keyNum; j > 1; j--)//结点关键字右移
            {
                mNode->keyword[j] = mNode->keyword[j - 1];
                mNode->kids[j] = mNode->kids[j - 1];
            }
            mNode->keyword[1] = parentNode->keyword[r];//父亲插入到结点
            mNode->kids[1] = mNode->kids[0];
            mNode->kids[0] = lc->kids[lc->keyNum];
            if (NULL != mNode->kids[0])//修改p中的子女的父结点为p
            {
                mNode->kids[0]->parent = mNode;
            }
            parentNode->keyword[parentNodeSubscript] = lc->keyword[lc->keyNum];//左兄弟上移到父亲位置
            lc->keyNum--;
            finished = 1;
            break;
        }
        else if (parentNode->keyNum > parentNodeSubscript && rc != NULL && (rc->keyNum > (m - 1) / 2)) //向右兄弟借关键字
        {
            mNode->keyNum++;
            mNode->keyword[mNode->keyNum] = parentNode->key[parentNodeSubscript]; //父亲插入到结点
            mNode->kids[mNode->keyNum] = rc->kids[0];
            if (NULL != mNode->kids[mNode->keyNum]) //修改p中的子女的父结点为p
                mNode->kids[mNode->keyNum]->parent = mNode;
            parentNode->keyword[parentNodeSubscript] = rc->keyword[1]; //右兄弟上移到父亲位置
            rc->kids[0] = rc->kids[1];
            for (j = 1; j < rc->keyNum; j++)  //右兄弟结点关键字左移
            {
                rc->keyword[j] = rc->keyword[j + 1];
                rc->kids[j] = rc->kids[j + 1];
            }
            rc->keyNum--;
            finished = 1;
            break;
        }

        parentNodeSubscript = 0;
        while (parentNode->kids[parentNodeSubscript] != mNode) //重新确定p在ap子树的位置
            parentNodeSubscript++;
        if (parentNodeSubscript > 0 && (parentNode->kids[parentNodeSubscript - 1]->keyNum <= (m - 1) / 2)) //与左兄弟合并
            //if(r>0) //与左兄弟合并
        {
            lc = parentNode->kids[parentNodeSubscript - 1];
            mNode->keyNum++;
            for (j = mNode->keyNum; j > 1; j--) //将p结点关键字和指针右移1位
            {
                mNode->keyword[j] = mNode->keyword[j - 1];
                mNode->kids[j] = mNode->kids[j - 1];
            }
            mNode->keyword[1] = parentNode->keyword[parentNodeSubscript]; //父结点的关键字与p合并
            mNode->kids[1] = mNode->kids[0]; //从左兄弟右移一个指针
            parentNode->kids[parentNodeSubscript] = lc;
            for (j = 1; j <= lc->keynum + p->keynum; j++) //将结点p中关键字和指针移到p左兄弟中
            {
                lc->key[lc->keynum + j] = p->key[j];
                lc->ptr[lc->keynum + j] = p->ptr[j];
            }
            if (p->ptr[0]) //修改p中的子女的父结点为lc
            {
                for (j = 1; j <= p->keynum; j++)
                    if (p->ptr[p->keynum + j])   p->ptr[p->keynum + j]->parent = lc;
            }
            lc->keynum = lc->keynum + p->keynum;  //合并后关键字的个数
            for (j = r; j < ap->keynum; j++)//将父结点中关键字和指针左移
            {
                ap->key[j] = ap->key[j + 1];
                ap->ptr[j] = ap->ptr[j + 1];
            }
            ap->keynum--;
            pr = p; free(pr);
            pr = NULL;
            p = lc;
        }
        else //与右兄弟合并
        {
            rc = ap->ptr[r + 1];
            if (r == 0)
                r++;
            p->keynum++;
            p->key[p->keynum] = ap->key[r]; //父结点的关键字与p合并
            p->ptr[p->keynum] = rc->ptr[0]; //从右兄弟左移一个指针
            rc->keynum = p->keynum + rc->keynum;//合并后关键字的个数
            ap->ptr[r - 1] = rc;
            for (j = 1; j <= (rc->keynum - p->keynum); j++)//将p右兄弟关键字和指针右移
            {
                rc->key[p->keynum + j] = rc->key[j];
                rc->ptr[p->keynum + j] = rc->ptr[j];
            }
            for (j = 1; j <= p->keynum; j++)//将结点p中关键字和指针移到p右兄弟
            {
                rc->key[j] = p->key[j];
                rc->ptr[j] = p->ptr[j];
            }
            rc->ptr[0] = p->ptr[0]; //修改p中的子女的父结点为rc
            if (p->ptr[0])
            {
                for (j = 1; j <= p->keynum; j++)
                    if (p->ptr[p->keynum + j])    p->ptr[p->keynum + j]->parent = rc;
            }
            for (j = r; j < ap->keynum; j++)//将父结点中关键字和指针左移
            {
                ap->key[j] = ap->key[j + 1];
                ap->ptr[j] = ap->ptr[j + 1];
            }
            ap->keynum--;//父结点的关键字个数减1
            pr = p;
            free(pr);
            pr = NULL;
            p = rc;
        }
        ap = ap->parent;
        if (p->parent->keynum >= (m - 1) / 2 || (NULL == ap && p->parent->keynum > 0))
            finished = 1;
        else if (ap == NULL) //若调整后出现空的根结点，则删除该根结点，树高减1
        {
            pr = T;
            T = p; //根结点下移
            free(pr);
            pr = NULL;
            finished = 1;
        }
        p = p->parent;
    }
}






