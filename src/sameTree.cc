#include "../include/common.h"

int main(int argc, char* argv[]) {
  TreeNode* t1 = new TreeNode(1);
  t1->left = new TreeNode(2);
  TreeNode* t2 = new TreeNode(1);
  t2->left = new TreeNode(2);
  ASSERT(areSameTree(t1, t2), "t1 should equal t2");
  return 0;
}
