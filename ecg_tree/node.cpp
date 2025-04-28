#include "node.h"
#include <collection.h>
#include <iostream>
#include <list>
#include <memory>
#include <ostream>
#include <set>
#include <stack>
#include <string>
#include <vector>

Node::Node(const std::string &n = "") : name(n) {
  node_id += 1;

  if (name.empty()) {
    name = "node_" + std::to_string(node_id);
  }

  children = std::vector<std::shared_ptr<Node>>();
}

// setup global object counter
int Node::node_id = 0;

Node::~Node() {
  std::cout << "enter ~node() of \"" << get_name() << "\"" << std::endl;
  children.clear();

  std::cout << "leave ~node() of \"" << get_name() << "\"" << std::endl;
}

std::string const &Node::get_name() const { return name; }

void Node::set_name(const std::string &new_name) { name = new_name; }

int Node::get_nr_children() const { return children.size(); }

std::shared_ptr<Node> Node::get_child(int i) const { return children[i]; }

void Node::add_child(std::shared_ptr<Node> child) { children.push_back(child); }

std::shared_ptr<Node> Node::create_complete_tree(int nr_child_nodes,
                                                 int tree_depth) {
  std::shared_ptr<Node> current = std::make_shared<Node>();

  if (tree_depth == 1) {
    return current;
  }
  for (int i = 0; i < nr_child_nodes; i++) {
    current->add_child(create_complete_tree(nr_child_nodes, tree_depth - 1));
  }
  return current;
}

void Node::print(std::ostream &str, int indent) const {
  std::string name = get_name();
  name.insert(name.begin(), indent * 3, ' ');
  str << name << std::endl;
  for (std::shared_ptr<Node> child : children) {
    child->print(str, indent + 1);
  }
}

void Node::print_cycle(std::ostream &str,
                       std::stack<std::shared_ptr<Node>> visitedstack,
                       std::shared_ptr<Node> target) const {
  std::shared_ptr<Node> current = visitedstack.top();
  while (current != target) {
    str << current->get_name() << std::endl;
    visitedstack.pop();
    current = visitedstack.top();
  }
  str << current->get_name() << std::endl;
}

void Node::print_detect_cycle(
    std::ostream &str, std::shared_ptr<Node> current,
    std::set<std::shared_ptr<Node>> visitedset,
    std::stack<std::shared_ptr<Node>> visitedstack) const {

  visitedset.insert(current);
  visitedstack.push(current);

  for (std::shared_ptr<Node> child : children) {
    // we first check whether child is in visited
    if (visitedset.count(child)) {
      print_cycle(str, visitedstack, child);
    } else {
      child->print_detect_cycle(str, child, visitedset, visitedstack);
    }
  }
  visitedstack.pop();
}

void Node::cleanup_cycles(std::shared_ptr<Node> current,
                          std::set<std::shared_ptr<Node>> visitedset) {
  visitedset.insert(current);
  for (std::shared_ptr<Node> &child : children) {
    if (visitedset.count(child)) {
      child.reset();
    } else {
      child->cleanup_cycles(child, visitedset);
    }
  }
}

extern std::ostream &operator<<(std::ostream &os, Node const &node) {
  node.print(os);
  return os;
}
