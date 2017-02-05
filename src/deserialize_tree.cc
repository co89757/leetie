#include "../include/common.h"

int main() {
  TreeNode* t = deserializeTree("1,2,3,4,#,5,#,6");
  ASSERT(t->left->left->val == 4, "");
  ASSERT(t->right->left->val == 5, " 5 is right");
  ASSERT(t->left->val == 2, "");
  ASSERT(t->left->left->left->val == 6, "6 is not there");
  auto s = serializeTree(t);
  puts(s.c_str());
  puts("\n");
}