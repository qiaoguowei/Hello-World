#include <iostream>

void buildTree(std::vector<int>& arr, std::vector<int>& tree, int start, int end, int node_idx)
{
    //递归的出口，也就是到了叶子节点
    if (start == end)
    {
        tree[node_idx] = arr[start];
    }
    else
    {
        int left_node = 2 * node_idx;
        int right_node = 2 * node_idx + 1;
        int mid = (start + end) / 2;

        buildTree(arr, tree, start, mid, left_node);
        buildTree(arr, tree, mid + 1, end, right_node);
        tree[node_idx] = tree[left_node] + tree[right_node];
    }
}

int query(std::vector<int>& arr, std::vector<int>& tree, int start, int end, int l, int r, int node_idx)
{
    //情况一
    if (l > end || r < start)
    {
        return 0;
    }
    else if (l <= start && r >= end) //情况二
    {
        std::cout << "此时的区间是[" << start << ", " << end << "]" << std::endl;
        std::cout << "区间和为 : " << tree[node_idx] << std::endl;
        return tree[node_idx];
    }
    else
    {
        int left_node = 2 * node_idx;
        int right_node = 2 * node_idx + 1;
        int mid = (left_node + right_node) / 2;

        int left_sum = query(arr, tree, start, mid, l, r, left_node);
        int right_sum = query(arr, tree, mid + 1, end, l, r, right_node);
        return left_sum + right_sum;
    }
}

void update(std::vector<int>& arr, std::vector<int>& tree, int start, int end, int node_idx, int update_idx, int val)
{
    //递归的出口，也就是找到了叶子节点，更新其值
    if (start == end)
    {
        tree[node_idx] = arr[start] = val;
    }
    else
    {
        //找到左子树节点(2 * node_idx)
        //找到右子树节点(2 * node_idx + 1)
        int left_node = 2 * node_idx;
        int right_node  = 2 * node_idx + 1;
        int mid = (start + end) / 2;
        //如果更新节点在右边
        if (update_idx > mid)
        {
            update(arr, tree, mid + 1, end, right_node, update_idx, val);
        }
        else
        {
            update(arr, tree, start, mid, left_node, update_idx, val);
        }
        tree[node_idx] = tree[left_node] + tree[right_node];
    }
}









