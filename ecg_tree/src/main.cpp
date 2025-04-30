#include "node.h"
#include <iostream>
#include <memory>
#include <string>

void task112() {
  std::string const &r = "root";
  std::string const &lc = "left child";
  std::string const &rc = "right child";

  auto root = std::make_shared<Node>(r);
  auto left_child = std::make_shared<Node>(lc);
  auto right_child = std::make_shared<Node>(rc);

  root->add_child(left_child);
  root->add_child(right_child);
}
void task122() {
  std::shared_ptr<Node> root = Node::create_complete_tree(2, 4, 0);
  std::cout << *root;
}
void task131() {
  auto root = Node::create_complete_tree(2, 4, 0);
  root->get_child(1)->get_child(1)->add_child(root);
  root->get_child(0)->get_child(1)->add_child(root);
  root->get_child(0)->get_child(0)->get_child(1)->add_child(root->get_child(0));
  root->print_detect_cycle(std::cout, root);
  // we need to get rid of cycles, or there will be memory leaks
  root->cleanup_cycles(root);
}
void task132() {
  auto root = Node::create_complete_tree(2, 4, 0);
  root->get_child(1)->get_child(1)->add_child(root);
  root->get_child(0)->get_child(1)->add_child(root);
  root->get_child(0)->get_child(0)->get_child(1)->add_child(root->get_child(0));
  root->print_detect_cycle_iter(std::cout, root);
  // we need to get rid of cycles, or there will be memory leaks
  root->cleanup_cycles(root);
}

int main() {
  task112();
  task122();
  task131();
  task132();
  return 0;
}
