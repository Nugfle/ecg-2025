#ifndef NODE_H
#define NODE_H

#include <collection.h>
#include <cstdio>
#include <memory>
#include <ostream>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <vector>

class Node {
private:
  std::string name;
  std::vector<std::shared_ptr<Node>> children;
  static int node_id;

  void print_cycle(std::ostream &str,
                   std::stack<std::shared_ptr<Node>> visitedstack,
                   std::shared_ptr<Node> target) const;

  static std::shared_ptr<Node> create_complete_tree_raw(int nr_child_nodes,
                                                        int tree_depth);

public:
  // the constructor
  Node(const std::string &name);
  // the destructor
  virtual ~Node();

  /// returns the name of the node as a string
  std::string const &get_name() const;

  /// sets the name of the node to name
  void set_name(const std::string &new_name);

  /// returns the number of current children
  int get_nr_children() const;

  /// returns a pointer to the ith child. I must not be negative or greater then
  /// or equal to get_nr_children()
  std::shared_ptr<Node> get_child(int i) const;

  /// adds the node as a child
  void add_child(std::shared_ptr<Node> node);

  /// creates a tree of given depth, where each node has nr_child_nodes
  /// children, so nr_child_nodes ^ tree_depth nodes
  static std::shared_ptr<Node>
  create_complete_tree(int nr_child_nodes, int tree_depth, int id = node_id);

  /// recursively prints the tree into the stream
  void print(std::ostream &str, int indent = 0) const;

  /// detects cycles and puts them into the stream
  void print_detect_cycle(std::ostream &str, std::shared_ptr<Node> current,
                          std::set<std::shared_ptr<Node>> visitedset =
                              std::set<std::shared_ptr<Node>>(),
                          std::stack<std::shared_ptr<Node>> visitedstack =
                              std::stack<std::shared_ptr<Node>>()) const;

  /// detects cycles and puts them into the stream, this method uses an
  /// iterative approach
  void print_detect_cycle_iter(std::ostream &str,
                               std::shared_ptr<Node> current) const;

  /// detects cycles and resolves them, by removing the "bad" references
  /// call this if your graph can contain cycles, to avoid memory leaks
  void cleanup_cycles(std::shared_ptr<Node> current,
                      std::set<std::shared_ptr<Node>> visitedset =
                          std::set<std::shared_ptr<Node>>());
};

extern std::ostream &operator<<(std::ostream &os, Node const &node);

#endif
