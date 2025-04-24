#include "node.h"

int main() {
  Node *root = new Node("root");
  Node *left_child = new Node("left child");
  Node *right_child = new Node("right child");
  // -> is used when accessing objects through pointers
  root->add_child(left_child);
  root->add_child(right_child);

  delete root;
  return 0;
}
