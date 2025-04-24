#include "node.h"
#include <iostream>
#include <string>
#include <vector>

Node::Node(const std::string &n) : name((std::string &)n) {
  children = std::vector<Node *>();
}

Node::~Node() {
  std::cout << "enter ~node() of \"";
  std::cout << get_name();
  std::cout << "\"\n";
  for (Node *child : children) {
    delete child;
  }
  std::cout << "leave ~node() of \"";
  std::cout << get_name();
  std::cout << "\"\n";
}

std::string &Node::get_name() const { return name; }

void Node::set_name(const std::string &new_name) { name = new_name; }

int Node::get_nr_children() const { return children.size(); }

Node *Node::get_child(int i) const { return children[i]; }

void Node::add_child(Node *child) { children.push_back(child); }
