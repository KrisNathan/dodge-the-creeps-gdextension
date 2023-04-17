#ifndef WILL_CRASH_HPP
#define WILL_CRASH_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/node_path.hpp>

#include "is_editor.hpp"

using namespace godot;

class ExportsNode : public Node {
  GDCLASS(ExportsNode, Node);

protected:
  static void _bind_methods();

private:
  ObjectID _node_a;
  ObjectID _node_b;

public:
  void _ready();

  void set_node_a(const Node2D *value);
  Node2D *get_node_a() const;

  void set_node_b(const Node *value);
  Node *get_node_b() const;
};

#endif