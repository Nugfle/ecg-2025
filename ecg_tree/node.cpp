#include "node.h"
#include <string>
#include <vector>

Node::Node(const std::string &n) : name(n), children(std::vector<Node *>()) {}
Node::~Node() {}

std::string const &Node::get_name() const { return name; }

void Node::set_name(std::string const &new_name) { name = new_name; }
int Node::get_nr_children() const { return children.size(); }
Node *Node::get_child(int i) const { return children[i]; }
void Node::add_child(Node *child) { children.push_back(child); }
