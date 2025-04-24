#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node {
private:
  std::string &name;
  std::vector<Node *> children;

public:
  Node(const std::string &name); // the constructor
  virtual ~Node();               // the destructor

  /// returns the name of the node as a string
  std::string &get_name() const;
  /// sets the name of the node to name
  void set_name(std::string &name);

  /// returns the number of current children
  int get_nr_children() const;
  /// returns a pointer to the ith child. I must not be negative or greater then
  /// or equal to get_nr_children()
  Node *get_child(int i) const;

  /// adds the node as a child
  void add_child(Node node);
};

#endif
