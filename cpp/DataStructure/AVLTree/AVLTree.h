#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include <memory>
#include <vector>

class AVLNode
{
public:
    AVLNode(const int& key);

    ~AVLNode();

    static int height(std::shared_ptr<AVLNode>& node);
    static void updateHeight(std::shared_ptr<AVLNode>& node);
    static int balanceFactor(std::shared_ptr<AVLNode>& node);

    static std::shared_ptr<AVLNode> rotateRight(std::shared_ptr<AVLNode>& node);
    static std::shared_ptr<AVLNode> rotateLeft(std::shared_ptr<AVLNode>& node);

    static std::shared_ptr<AVLNode> avlInsert(std::shared_ptr<AVLNode>& node, int key);
    static std::shared_ptr<AVLNode> avlDelete(std::shared_ptr<AVLNode>& node, int key);
    static std::shared_ptr<AVLNode> avlSearch(std::shared_ptr<AVLNode>& node, int key);

    static void inorder(std::shared_ptr<AVLNode>& node, std::vector<int>& res);

private:
    static std::shared_ptr<AVLNode> balance(std::shared_ptr<AVLNode>& node);
    static std::shared_ptr<AVLNode> minValueNode(std::shared_ptr<AVLNode>& node);

public:
    int key;
    int delete_key;
    std::shared_ptr<AVLNode> left;
    std::shared_ptr<AVLNode> right;
    int m_height;
};


#endif //_AVL_TREE_H
