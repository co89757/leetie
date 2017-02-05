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

static TreeNode* rdeserializeTree(const std::vector<string>& v, int i) {
  int N = v.size();
  string val = v.at(i);
  if (val == "#") return NULL;
  int key = std::stoi(val);
  TreeNode* t = new TreeNode(key);
  auto i_leftchild = (i << 1) + 1;
  auto i_rightchild = (i << 1) + 2;
  if (i_leftchild < N) t->left = rdeserializeTree(v, i_leftchild);
  if (i_rightchild < N) t->right = rdeserializeTree(v, i_rightchild);
  return t;
}

TreeNode* deserializeTree(const char* s) {
  if (s == NULL || s[0] == '\0') return NULL;
  std::vector<string> tokens = split(s, ", \t");
  if (tokens.empty()) return NULL;
  TreeNode* t = rdeserializeTree(tokens, 0);
  return t;
}

string serializeTree(TreeNode* root) {
  if (!root) return "";
  // use two queues to do level-order traversal of tree
  deque<TreeNode*> q;
  deque<TreeNode*> qnext;
  q.push_back(root);
  vector<string> v;
  while (!q.empty()) {
    TreeNode* front = q.front();
    if (!front) {
      v.push_back("#");
    } else {
      v.push_back(std::to_string(front->val));
    }
    if (front) {
      qnext.push_back(front->left);
      qnext.push_back(front->right);
    }

    q.pop_front();

    if (q.empty()) {
      // terminate the loop if no more next level to print
      bool isEnd =
          std::none_of(begin(qnext), end(qnext), [](TreeNode* x) { return x; });
      if (isEnd) break;
      // advance to next level
      q.swap(qnext);
    }
  }

  string res;
  for (auto it = begin(v); it != end(v); it++) {
    if (it == begin(v)) {
      res += *it;
    } else {
      res = res + "," + *it;
    }
  }

  return res;
}
