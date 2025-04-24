#include "node.h"

int main() {
  Node *root = new Node("root");
  Node *left_child = new Node("left child");
  Node *right_child = new Node("right child");
  delete root;
  return 0;
}
