#include <iostream>

struct ListNode
{
public:
    ListNode()
        : val(0)
        , next(nullptr)
    {}

    ListNode(int x)
        : val(x)
        , next(nullptr)
    {}

    ListNode(int x, ListNode *next)
        : val(x)
        , next(next)
    {}

public:
    int val;
    ListNode *next;
};

class Solution
{
public:
    std::pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail)
    {
        ListNode* prev = tail->next;
        ListNode* p = head;

        while (prev != tail)
        {
            ListNode *next_p = p->next;
            p->next = prev;
            prev = p;
            p = next_p;
        }

        return {tail, head};
    }

    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *hair = new ListNode(0);
        hair->next = head;
        ListNode *pre = hair;

        while (head)
        {
            ListNode *tail = pre;
            //查看剩余部分长度是否大于等于k
            for (int i = 0; i < k; ++i)
            {
                tail = tail->next;
                if (!tail)
                {
                    return hair->next;
                }
            }

            ListNode *nex = tail->next;

            std::tie(head, tail) = myReverse(head, tail);
            //把子链表重新接回原链表
            pre->next = head;
            tail->next = nex;
            pre = tail;
            head = tail->next;
        }

        return hair->next;
    }

};

int main()
{
    ListNode *node4 = new ListNode(4);
    ListNode *node3 = new ListNode(3, node4);
    ListNode *node2 = new ListNode(2, node3);
    ListNode *node1 = new ListNode(1, node2);

    ListNode *head = new ListNode(0);
    head->next = node1;

    for (ListNode *p = head->next; p != nullptr; p = p->next)
    {
        std::cout << p->val << ", ";
    }
    std::cout << std::endl;

    Solution s;
    auto node_pair = s.myReverse(node1, node4);
    head->next = node_pair.first;

    for (ListNode *p = head->next; p != nullptr; p = p->next)
    {
        std::cout << p->val << ", ";
    }
    std::cout << std::endl;

    for (ListNode *p = head; p != nullptr;)
    {
        ListNode *tmp_node = p;
        p = p->next;
        delete tmp_node;
    }
}




