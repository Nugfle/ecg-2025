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
  // std::cout << "enter ~node() of \"" << get_name() << "\"" << std::endl;
  children.clear();
  // std::cout << "leave ~node() of \"" << get_name() << "\"" << std::endl;
}

std::string const &Node::get_name() const { return name; }

void Node::set_name(const std::string &new_name) { name = new_name; }

int Node::get_nr_children() const { return children.size(); }

std::shared_ptr<Node> Node::get_child(int i) const { return children[i]; }

void Node::add_child(std::shared_ptr<Node> child) { children.push_back(child); }

std::shared_ptr<Node> Node::create_complete_tree_raw(int nr_child_nodes,
                                                     int tree_depth) {
  std::shared_ptr<Node> current = std::make_shared<Node>();
  if (tree_depth == 1) {
    return current;
  }
  for (int i = 0; i < nr_child_nodes; i++) {
    current->add_child(
        create_complete_tree_raw(nr_child_nodes, tree_depth - 1));
  }
  return current;
}

std::shared_ptr<Node> Node::create_complete_tree(int nr_child_nodes,
                                                 int tree_depth, int id) {
  node_id = id;
  return create_complete_tree_raw(nr_child_nodes, tree_depth);
}

void Node::print(std::ostream &str, int indent) const {
  std::string name = get_name();
  name.insert(name.begin(), indent * 3, ' ');
  str << name << std::endl;
  for (std::shared_ptr<Node> child : children) {
    child->print(str, indent + 1);
  }
}

// we walk back up until we find the node that we are in a cycle with
void Node::print_cycle(std::ostream &str,
                       std::stack<std::shared_ptr<Node>> visitedstack,
                       std::shared_ptr<Node> target) const {
  std::shared_ptr<Node> current = visitedstack.top();
  str << "cycle found:  " << std::endl;
  int i = 1;
  while (current != target) {
    str << i << ". " << current->get_name() << std::endl;
    visitedstack.pop();
    current = visitedstack.top();
    i++;
  }
  str << i << ". " << current->get_name() << std::endl;
}

/* we use a set for logarithmic search and a stack for easy printing, this is
 * basic  dfs*/
void Node::print_detect_cycle(
    std::ostream &str, std::shared_ptr<Node> current,
    std::set<std::shared_ptr<Node>> visitedset,
    std::stack<std::shared_ptr<Node>> visitedstack) const {

  visitedset.insert(current);
  visitedstack.push(current);

  for (auto child : children) {
    // checks whether child is in visited
    if (visitedset.count(child)) {
      // we know there is a path from every node in the set to our current node,
      // because we pass by value, this means, that all we have to do now is
      // walk up the stack until we find the node that creates the cycle
      print_cycle(str, visitedstack, child);
    } else {
      // we just keep going deeper
      child->print_detect_cycle(str, child, visitedset, visitedstack);
    }
  }
  visitedstack.pop();
}

void Node::print_detect_cycle_iter(std::ostream &str,
                                   std::shared_ptr<Node> start) const {
  // holds all the unvisited nodes
  auto unvisited = std::stack<std::shared_ptr<Node>>();
  // keeps track of the path from root to current
  auto path = std::stack<std::shared_ptr<Node>>();
  // same as path, but as a set for fast and easy access
  auto pathset = std::set<std::shared_ptr<Node>>();

  unvisited.push(start);

  while (!unvisited.empty()) {
    auto current = unvisited.top();
    unvisited.pop();
    bool is_leaf = true;

    for (auto child : current->children) {
      if (pathset.count(child)) {
        path.push(current);
        print_cycle(str, path, child);
        path.pop();
      } else {
        unvisited.push(child);
        is_leaf = false;
      }
    }
    if (!is_leaf) {
      // we go one level deeper
      path.push(current);
      pathset.insert(current);
    } else {
      // we go one level up so we remove the current node from unvisited and try
      // to find the next nodes parent, which will be the top of our path stack
      bool found = false;
      // we pop from the stack until we find the node, that pushed this child
      // onto the stack
      if (unvisited.empty()) {
        return;
      }
      while (!found) {
        for (auto child : path.top()->children) {
          if (child == unvisited.top()) {
            found = true;
            break;
          }
        }
        if (!found) {
          pathset.erase(path.top());
          path.pop();
        }
      }
    }
  }
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
