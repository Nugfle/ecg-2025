#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node {
private:
  std::string name;
  std::vector<Node *> children;
  static int node_id;

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
  Node *get_child(int i) const;

  /// adds the node as a child
  void add_child(Node *node);

  /// creates a tree of given depth, where each node has nr_child_nodes
  /// children, so nr_child_nodes ^ tree_depth nodes
  static Node *create_complete_tree(int nr_child_nodes, int tree_depth);
};

#endif
