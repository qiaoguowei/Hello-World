#include "AVLTree.h"
#include <iostream>

AVLNode::AVLNode(const int& key)
    : key(key)
    , delete_key(key)
    , m_height(1)
{
}

AVLNode::~AVLNode()
{
    std::cout << "destructure... key = [" << delete_key << "]" << std::endl;
}

int AVLNode::height(std::shared_ptr<AVLNode>& node)
{
    if (node)
        return node->m_height;
    return 0;
}

void AVLNode::updateHeight(std::shared_ptr<AVLNode>& node)
{
    node->m_height = 1 + std::max(height(node->left), height(node->right));
}

int AVLNode::balanceFactor(std::shared_ptr<AVLNode>& node)
{
    if (node)
        return height(node->left) - height(node->right);
    return 0;
}

/*
        A               l
       /      ------     \
      l                   A
       \                 /
        r               r
 */
std::shared_ptr<AVLNode> AVLNode::rotateRight(std::shared_ptr<AVLNode>& node)
{
    std::shared_ptr<AVLNode> node_left = node->left;
    std::shared_ptr<AVLNode> node_left_right = node_left->right;

    //旋转
    node_left->right = node;
    node->left = node_left_right;

    //更新高度
    updateHeight(node);
    updateHeight(node_left);
    return node_left;
}

/*
            A                      r
             \                    /
              r      -------     A  
             /                    \
            l                      l
 */
std::shared_ptr<AVLNode> AVLNode::rotateLeft(std::shared_ptr<AVLNode>& node)
{
    std::shared_ptr<AVLNode> node_right = node->right;
    std::shared_ptr<AVLNode> node_right_left = node_right->left;

    //旋转
    node_right->left = node;
    node->right = node_right_left;

    //更新高度
    updateHeight(node);
    updateHeight(node_right);
    return node_right;
}

std::shared_ptr<AVLNode> AVLNode::balance(std::shared_ptr<AVLNode>& node)
{
    //更新高度和检查平衡
    updateHeight(node);
    int bf = balanceFactor(node);

    // LL
    if (bf > 1 && balanceFactor(node->left) >= 0)
        return rotateRight(node);
    // RR
    if (bf < -1 && balanceFactor(node->right) <= 0)
        return rotateLeft(node);
    // LR
    if (bf > 1 && balanceFactor(node->left) < 0)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // RL
    if (bf < -1 && balanceFactor(node->right) > 0)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

std::shared_ptr<AVLNode> AVLNode::avlInsert(std::shared_ptr<AVLNode>& node, int key)
{
    if (!node)
        return std::make_shared<AVLNode>(key);

    if (key < node->key)
        node->left = avlInsert(node->left, key);
    else if (key > node->key)
        node->right = avlInsert(node->right, key);
    else //重复键，这里简单忽略
        return node;


    return balance(node);
}

std::shared_ptr<AVLNode> AVLNode::minValueNode(std::shared_ptr<AVLNode>& node)
{
    std::shared_ptr<AVLNode> current = node;

    while (current->left)
        current = current->left;

    return current;
}

std::shared_ptr<AVLNode> AVLNode::avlDelete(std::shared_ptr<AVLNode>& node, int key)
{
    if (!node)
        return node;

    // 普通 BST 删除
    if (key < node->key)
        node->left = avlDelete(node->left, key);
    else if (key > node->key)
        node->right = avlDelete(node->right, key);
    else
    {
        // 找到要删除的节点
        if (!node->left)
            return node->right;
        else if (!node->right)
            return node->left;
        else
        {
            // 有两个子节点：取右子树最小值
            std::shared_ptr<AVLNode> temp_node = minValueNode(node->right);
            node->key = temp_node->key;
            node->right = avlDelete(node->right, temp_node->key);
        }
    }

    if (node)
        return balance(node);

    return std::shared_ptr<AVLNode>();
}

std::shared_ptr<AVLNode> AVLNode::avlSearch(std::shared_ptr<AVLNode>& node, int key)
{
    if (!node)
        return nullptr;
    if (key == node->key)
        return node;
    else if (key < node->key)
        return avlSearch(node->left, key);
    else if (key > node->key)
        return avlSearch(node->right, key);

    return nullptr;
}

void AVLNode::inorder(std::shared_ptr<AVLNode>& node, std::vector<int>& res)
{
    if (node)
    {
        inorder(node->left, res);
        res.push_back(node->key);
        inorder(node->right, res);
    }
}







