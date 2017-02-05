#include "../include/common.h"
#include <stack>
using std::stack;
ListNode* createList(const std::initializer_list<int>& keys) {
  ListNode* dummy = new ListNode(0);
  ListNode* cur = dummy;
  for (auto k : keys) {
    cur->next = new ListNode(k);
    cur = cur->next;
  }

  auto result = dummy->next;
  dummy->next = NULL;
  delete dummy;
  return result;
}

void printList(ListNode* head) {
  if (!head) return;
  while (head) {
    if (head->next == NULL)
      printf("%d\n", head->val);
    else
      printf("%d -> ", head->val);
    head = head->next;
  }
}

void freeList(ListNode* head) {
  stack<ListNode*> st;
  while (head) {
    st.push(head);
    head = head->next;
  }

  while (!st.empty()) {
    ListNode* top = st.top();
    delete top;
    st.pop();
  }
}