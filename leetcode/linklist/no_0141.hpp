// 判断链表是否有环
#include "../include/core.h"


 //Definition for singly-linked list.
 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
 };

class Solution_0141 {
public:
    // 解法一：使用 set 数据结构，存放已经访问过的节点的地址
    // 时间复杂度：O(n)
    // 空间复杂度：O(n)
    bool hasCycle1(ListNode *head) {
        std::set<ListNode*> nodes_set;

        ListNode *tmp = head;
        while (tmp) {
            if (nodes_set.count(tmp) == 1) {
                return true;
            }

            nodes_set.insert(tmp);
            tmp = tmp->next;
        }

        return false;        
    }

    // 解法二：使用快慢指针，如果存在环，则一定会相遇
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    bool hasCycle(ListNode *head) {
        // 初始时，快慢指针指向第一个节点
        ListNode *slow = head;
        ListNode *fast = head;

        while (fast && fast->next) {
            // 慢指针走一步
            slow = slow->next;
            // 快指针走两步
            fast = fast->next->next;

            // 如果存在环，则快慢指针一定会相遇
            if (slow == fast) {
                return true;
            }
        }

        return false;
    }
};
