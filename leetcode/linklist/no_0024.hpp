#include "../include/core.h"

 //Definition for singly-linked list.
 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
 };

class Solution_0024 {
public:
    // TODO：递归
    ListNode* swapPairs(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode *next = head->next;
        head->next = swapPairs(next->next);
        next->next = head;
        return next;
    }

    // 直接法
    ListNode* swapPairs1(ListNode* head) {
        ListNode dummy(-1);
        dummy.next = head;

        ListNode *tmp_dummy = &dummy;
        while (tmp_dummy->next && tmp_dummy->next->next) {
            ListNode *a = tmp_dummy->next;
            ListNode *b = tmp_dummy->next->next;

            a->next = b->next;
            b->next = a;
            tmp_dummy->next = b;
            tmp_dummy = a;
        }

        return dummy.next;           
    }
};