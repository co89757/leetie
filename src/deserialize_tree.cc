#include "../include/common.h"

int main() {
  TreeNode* t = deserializeTree("1,2,3,#,#,4,5");
  auto s = serializeTree(t);
  puts(s.c_str());
  puts("\n");
}