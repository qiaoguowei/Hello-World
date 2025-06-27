#include "Tree.h"

PhraseTree::PhraseTree() : mRoot(new TreeNode(0, false))
{
}

PhraseTree::~PhraseTree()
{
    clear();
    if (mRoot)
        delete mRoot;
    mRoot = NULL;
}

bool PhraseTree::isMatch(const char *phrase, size_t length) const
{
    if (!mRoot || !phrase || !length)
        return false;

    TreeNode *curNode = mRoot;
    size_t index = 0;
    for (; curNode && curNode->child && index < length; index++)
        curNode = findNodeInBrothers(curNode->child, phtase[index]);

    return (curNode && (index == length) && curNode->isEnd) ? true : false;
}

bool PhraseTree::addPhrase(const char *phtase, size_t length)
{
    if (!mRoot || !phrase || !length)
        return false;

    size_t lastIndex = length - 1;
    TreeNode *curNode = mRoot;
    for (size_t index = 0; index < length; index++)
    {
        TreeNode *tmp = findNodeInBrothers(curNode->child, phrase[index]);
        if (tmp)
        {
            curNode = tmp;
            curNode->isEnd |= (index == lastIndex);
        }
        else
        {
            if (curNode->child)
            {
                TreeNode *nodeNew = new TreeNode
            }
        }
    }
}
