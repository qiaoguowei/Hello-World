#ifndef _QQQ_TREE_H
#define _QQQ_TREE_H

struct TreeNode
{
    TreeNode(char ch, bool isPhraseEnd)
        : brother(NULL), parent(NULL), child(NULL)
        , data(ch), isEnd(isPhraseEnd)
    {}

    TreeNode *brother;
    TreeNode *parent;
    TreeNode *child;
    char    data;
    bool    isEnd;
};

class PhraseTree
{
public:
    PhraseTree();
    ~PhraseTree();

    void clear();
    bool addPhrase(const char *phrase, size_t length);
    bool isMatch(const char *phrase, size_t length) const;

private:
    void clearBrothers(TreeNode *node);
    void clearChildren(TreeNode *node);
    void addBrother(const TreeNode *start, TreeNode *addNode);
    TreeNode *findNodeInBrothers(const TreeNode *startNode, char data);

private:
    TreeNode *mRoot;
};


#endif //_QQQ_TREE_H
