#include "../include/common.h"

int main() {
  TreeNode* t = deserializeTree("5,2,#,#,3,2,3,#,#,1,#,#,4");
  ASSERT(t->left->val == 2, "2 is not there");
  ASSERT(t->right->left->val == 2, " 2 is not right");
  ASSERT(t->right->val == 3, "");
  ASSERT(t->right->left->left->val == 3, "last 3 is missing");
  ASSERT(t->right->left->right->val == 1, "last 1 is missing");
  auto s = serializeTree(t);
  puts(s.c_str());
  puts("\n");
}