#include "exports_node.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


void ExportsNode::_bind_methods() {
  ClassDB::bind_method(D_METHOD("set_node_a", "value"), &ExportsNode::set_node_a);
  ClassDB::bind_method(D_METHOD("get_node_a"), &ExportsNode::get_node_a);
  ClassDB::bind_method(D_METHOD("set_node_b", "value"), &ExportsNode::set_node_b);
  ClassDB::bind_method(D_METHOD("get_node_b"), &ExportsNode::get_node_b);

  ADD_GROUP("Deps", "");
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "node_a", PROPERTY_HINT_NODE_TYPE,
                            "Node2D"),
               "set_node_a", "get_node_a");
  ADD_PROPERTY(
      PropertyInfo(Variant::OBJECT, "node_b", PROPERTY_HINT_NODE_TYPE, "Node"),
      "set_node_b", "get_node_b");
}

void ExportsNode::_ready() {
    if (IS_EDITOR())
        return;

    UtilityFunctions::print(get_node_a());
}

void ExportsNode::set_node_a(const Node2D *value) {
  if (value != nullptr) {
    _node_a = value->get_instance_id();
  } else {
    _node_a = ObjectID();
  }
}
Node2D *ExportsNode::get_node_a() const { 
    auto object = ObjectDB::get_instance(_node_a);
    return Object::cast_to<Node2D>(object); 
}

void ExportsNode::set_node_b(const Node *value) {
  if (value != nullptr) {
    _node_b = value->get_instance_id();
  } else {
    _node_b = ObjectID();
  }
}
Node *ExportsNode::get_node_b() const { 
    auto object = ObjectDB::get_instance(_node_b);
    return Object::cast_to<Node>(object); 
}