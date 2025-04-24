#include "node.h"
#include <string>
#include <vector>

Node::Node(const std::string &n) : name(n), children(std::vector<Node *>()) {}
Node::~Node() {}

std::string &Node::get_name() const {}
void Node::set_name(std::string &new_name) {}
int Node::get_nr_children() const {}
Node *Node::get_child(int i) const {}
void Node::add_child(Node child) {}
