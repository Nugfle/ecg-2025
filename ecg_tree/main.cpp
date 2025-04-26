#include "node.h"
#include <iostream>
#include <string>

void task112() {
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
void task122() {
  Node *root = Node::create_complete_tree(2, 4);
  std::cout << *root;
  delete root;
}

int main() {
  task112();
  task122();
  return 0;
}
