#include "AVLTree.h"
#include <iostream>

int main()
{
    std::vector<int> keys = {10, 20, 30, 40, 50, 25};
    std::shared_ptr<AVLNode> head;
    for (int& key : keys)
    {
        head = AVLNode::avlInsert(head, key);
    }

    std::vector<int> results;
    AVLNode::inorder(head, results);
    for (int& result : results)
    {
        std::cout << result << ", ";
    }
    std::cout << std::endl;
    results.clear();

    AVLNode::avlDelete(head, 25);
    AVLNode::avlDelete(head, 30);
    AVLNode::inorder(head, results);
    for (int& result : results)
    {
        std::cout << result << ", ";
    }
    std::cout << std::endl;
}
