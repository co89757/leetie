#include "../include/common.h"

// You are given two non-empty linked lists representing two non-negative
// integers. The digits are stored in reverse order and each of their nodes
// contain a single digit. Add the two numbers and return it as a linked list.

// You may assume the two numbers do not contain any leading zero, except the
// number 0 itself.

// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8
ListNode* add_two_numbers(ListNode* l1, ListNode* l2) {
  int digit = 0;
  int carry = 0;
  ListNode* dummy = new ListNode(0);
  ListNode* cur = dummy;
  while (l1 && l2) {
    int sum = l1->val + l2->val + carry;
    digit = sum % 10;
    carry = sum / 10;
    cur->next = new ListNode(digit);
    l1 = l1->next;
    l2 = l2->next;
    cur = cur->next;
  }

  auto l = l1 ? l1 : l2;  // the longer list
  while (l) {
    int sum = l->val + carry;
    digit = sum % 10;
    carry = sum / 10;
    cur->next = new ListNode(digit);
    cur = cur->next;
    l = l->next;
  }

  if (carry != 0) {
    cur->next = new ListNode(carry);
  }

  ListNode* res = dummy->next;
  dummy->next = NULL;
  delete dummy;
  return res;
}

int main() {
  ListNode* l1 = createList({1});
  ListNode* l2 = createList({9, 9});
  ListNode* r = add_two_numbers(l1, l2);
  printList(r);
  freeList(l1);
  freeList(l2);
  freeList(r);
}
