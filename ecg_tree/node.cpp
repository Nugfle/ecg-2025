#include "node.h"
#include <iostream>
#include <string>
#include <vector>

Node::Node(const std::string &n = "") : name(n) {
  node_id += 1;

  if (name.empty()) {
    name = "node_" + std::to_string(node_id);
  }

  children = std::vector<Node *>();
}

// setup global object counter
int Node::node_id = 0;

Node::~Node() {
  std::cout << "enter ~node() of \"" << get_name() << "\"" << std::endl;
  for (Node *child : children) {
    delete child;
  }
  std::cout << "leave ~node() of \"" << get_name() << "\"" << std::endl;
}

std::string const &Node::get_name() const { return name; }

void Node::set_name(const std::string &new_name) { name = new_name; }

int Node::get_nr_children() const { return children.size(); }

Node *Node::get_child(int i) const { return children[i]; }

void Node::add_child(Node *child) { children.push_back(child); }

Node *Node::create_complete_tree(int nr_child_nodes, int tree_depth) {
  Node *current = new Node;

  if (tree_depth == 1) {
    return current;
  }
  for (int i = 0; i < nr_child_nodes; i++) {
    current->add_child(
        current->create_complete_tree(nr_child_nodes, tree_depth - 1));
  }
  return current;
}
