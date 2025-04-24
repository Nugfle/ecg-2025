#include "node.h"
#include <iostream>
#include <string>

void task11() {
  std::string const &r = "root";
  std::string const &lc = "left child";
  std::string const &rc = "right child";

  Node *root = new Node(r);
  Node *left_child = new Node(lc);
  Node *right_child = new Node(rc);
  // -> is used when accessing objects through pointers
  root->add_child(left_child);
  root->add_child(right_child);
  delete root;
}

int main() {
  task11();
  return 0;
}
