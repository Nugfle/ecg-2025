#include "node.h"
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

void task112() {
  std::string const &r = "root";
  std::string const &lc = "left child";
  std::string const &rc = "right child";

  auto root = std::make_shared<Node>(r);
  auto left_child = std::make_shared<Node>(lc);
  auto right_child = std::make_shared<Node>(rc);
  // -> is used when accessing objects through pointers
  root->add_child(left_child);
  root->add_child(right_child);
}
void task122() {
  std::shared_ptr<Node> root = Node::create_complete_tree(2, 4);
  std::cout << *root;
}
void task131() {
  auto root = Node::create_complete_tree(2, 4);
  root->get_child(1)->get_child(1)->add_child(root);
  root->print_detect_cycle(std::cout, root);
  root->cleanup_cycles(root);
}

int main() {
  task112();
  task122();
  task131();
  return 0;
}
