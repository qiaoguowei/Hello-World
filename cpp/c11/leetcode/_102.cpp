#include <iostream>
#include <boost/scope_exit.hpp>
#include <vector>
#include <stack>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    std::vector<std::vector<int>> levelOrder(TreeNode *root)
    {
        std::vector<std::vector<int>> result;
        std::stack<std::vector<TreeNode *>> treenode_stack;
        if (root)
        {
            std::vector<TreeNode*> treenode_vec;
            treenode_vec.push_back(root);
            treenode_stack.push(treenode_vec);
            std::vector<int> the_same_layer_val;
            the_same_layer_val.push_back(root->val);
            result.push_back(the_same_layer_val);
        }

        while (!treenode_stack.empty())
        {
            std::vector<TreeNode *>& treenode_vec = treenode_stack.top();
            std::vector<TreeNode *> the_same_layer_node;
            std::vector<int> the_same_layer_val;
            for (TreeNode *treenode : treenode_vec)
            {
                if (treenode->left)
                {
                    the_same_layer_node.push_back(treenode->left);
                    the_same_layer_val.push_back(treenode->left->val);
                }
                if (treenode->right)
                {
                    the_same_layer_node.push_back(treenode->right);
                    the_same_layer_val.push_back(treenode->right->val);
                }
            }

            treenode_stack.pop();
            if (!the_same_layer_node.empty())
            {
                treenode_stack.push(the_same_layer_node);
                result.push_back(the_same_layer_val);
            }
        }

        return result;
    }
};

int main()
{
    TreeNode *root = new TreeNode(3);

    TreeNode *level1_1 = new TreeNode(9);
    root->left = level1_1;
    TreeNode *level1_2 = new TreeNode(20);
    root->right = level1_2;

    TreeNode *level2_3 = new TreeNode(15);
    level1_2->left = level2_3;
    TreeNode *level2_4 = new TreeNode(7);
    level1_2->right = level2_4;

    BOOST_SCOPE_EXIT(&root, &level1_1, &level1_2, &level2_3, &level2_4)
    {
        if (root)
        {
            delete root;
            root = nullptr;
            std::cout << "delete root" << std::endl;
        }
        if (level1_1)
        {
            delete level1_1;
            level1_1 = nullptr;
            std::cout << "delete level1_1" << std::endl;
        }
        if (level1_2)
        {
            delete level1_2;
            level1_2 = nullptr;
            std::cout << "delete level1_2" << std::endl;
        }
        if (level2_3)
        {
            delete level2_3;
            level2_3 = nullptr;
            std::cout << "delete level2_3" << std::endl;
        }
        if (level2_4)
        {
            delete level2_4;
            level2_4 = nullptr;
            std::cout << "delete level2_4" << std::endl;
        }
    }BOOST_SCOPE_EXIT_END

    Solution s;
    std::vector<std::vector<int>> result = s.levelOrder(root);

    for (auto the_same_layer_result : result)
    {
        std::cout << "============================" << std::endl;
        for (auto the_single_result : the_same_layer_result)
        {
            std::cout << the_single_result << ", ";
        }
        std::cout << std::endl;
    }
}




