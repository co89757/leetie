#include <algorithm>
#include <queue>
#include <stdexcept>
#include "../include/common.h"

using std::priority_queue;
using std::vector;
struct NodeCompare {
  bool reverse;
  NodeCompare(bool rev = false) : reverse(rev) {}

  // return true iff l is less than r
  bool operator()(const ListNode* l, const ListNode* r) {
    bool less = false;
    if (!l || !r) THROW_FMT(std::invalid_argument, "null pointer error");
    less = l->val < r->val;
    if (reverse) less = !less;
    return less;
  }
};

typedef priority_queue<ListNode*, std::vector<ListNode*>, NodeCompare>
    listnode_heap;

ListNode* merge_k_sorted_lists(const vector<ListNode*>& lists) {
  listnode_heap hp(NodeCompare(true));
  ListNode* dummy = new ListNode(0);
  ListNode* cur = dummy;
  // init
  for_each(lists.begin(), lists.end(), [&hp](ListNode* n) {
    if (n) {
      hp.push(n);
    }
  });

  while (!hp.empty()) {
    ListNode* top = hp.top();
    cur->next = new ListNode(top->val);
    hp.pop();
    // replenish the heap if it has next
    if (top->next) {
      hp.push(top->next);
    }
    cur = cur->next;
  }

  ListNode* result = dummy->next;
  dummy->next = NULL;
  delete dummy;
  return result;
}

int main() {
  ListNode* l1 = createList({3, 7, 9, 10});
  ListNode* l2 = createList({1, 2, 8});
  ListNode* l3 = createList({0, 11, 13});
  ListNode* l4 = NULL;
  vector<ListNode*> v{l1, l2, l3, l4};
  ListNode* r = merge_k_sorted_lists(v);
  ListNode* expected = createList({0, 1, 2, 3, 7, 8, 9, 10, 11, 13});
  ASSERT(areSameList(r, expected), "result is not sorted");
  printList(r);
  freeList(expected);
  freeList(l1);
  freeList(l2);
  freeList(l3);
  freeList(r);
}
