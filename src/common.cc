#include "../include/common.h"
#include <algorithm>
#include <cstring>
#include <deque>
#include <iterator>
#include <queue>
#include <sstream>
#include <stack>
using std::stack;
using std::deque;
using std::string;
using std::vector;
using std::queue;
using std::begin;
using std::end;

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

std::vector<string> split(const char* s, const char* delim) {
  std::vector<string> v;
  // to avoid modifying original string
  // first duplicate the original string and return a char pointer then free the
  // memory
  char* dup = strdup(s);
  char* token = strtok(dup, delim);
  while (token != NULL) {
    v.push_back(string(token));
    // the call is treated as a subsequent calls to strtok:
    // the function continues from where it left in previous invocation
    token = strtok(NULL, delim);
  }
  free(dup);

  return v;
}

void tree_preorderPrint(TreeNode* root) {
  if (root == NULL) {
    printf(" # ");
    return;
  }
  printf(" %d ", root->val);
  tree_preorderPrint(root->left);
  tree_preorderPrint(root->right);
}

void tree_postorderPrint(TreeNode* root) {
  if (root == NULL) {
    printf(" # ");
    return;
  }
  printf(" %d ", root->val);
  tree_postorderPrint(root->left);
  tree_postorderPrint(root->right);
}

static TreeNode* rdeserializeTree(const vector<string>& keys, size_t& offset) {
  // TODO
  size_t N = keys.size();
  if (offset >= N) return NULL;
  string val = keys.at(offset);
  offset++;
  if (val == "#") return NULL;
  int data = std::stoi(val);
  TreeNode* t = new TreeNode(data);
  t->left = rdeserializeTree(keys, offset);
  t->right = rdeserializeTree(keys, offset);
  return t;
}

TreeNode* deserializeTree(const char* s) {
  if (s == NULL || s[0] == '\0') return NULL;
  auto v = split(s, ", \t");
  size_t offset = 0;
  TreeNode* t = rdeserializeTree(v, offset);
  return t;
}

void rserializeTree(TreeNode* r, vector<string>& keys) {
  if (!r) {
    keys.push_back("#");
    return;
  }

  string data = std::to_string(r->val);
  keys.push_back(data);
  rserializeTree(r->left, keys);
  rserializeTree(r->right, keys);
}

string serializeTree(TreeNode* root) {
  vector<string> keys;
  rserializeTree(root, keys);
  string res;
  for (auto it = keys.begin(); it != keys.end(); it++) {
    if (it != keys.begin())
      res = res + "," + *it;
    else
      res += *it;
  }
  return res;
}
