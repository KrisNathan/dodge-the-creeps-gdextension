#ifndef PLAYER_H
#define PLAYER_H

#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/godot.hpp>

class Player : public godot::Area2D {
  GDCLASS(Player, godot::Area2D);

private:
  godot::Input *_input_object;
  godot::Vector2 _screen_size; // Size of the game window.

protected:
  static void _bind_methods();

public:
  godot::AnimatedSprite2D *animated_sprite;
  godot::CollisionShape2D *collision_shape;
  real_t speed = 400; // How fast the player will move (pixels/sec).

  void _init() {}
  void _ready();
  void _process(const double p_delta);
  void start(const godot::Vector2 p_position);
  void on_body_entered(godot::Node2D *_body);

  void set_collision_shape(godot::CollisionShape2D *collision_shape);
  godot::CollisionShape2D *get_collision_shape();

  void set_animated_sprite(godot::AnimatedSprite2D *animated_sprite);
  godot::AnimatedSprite2D *get_animated_sprite();
};

#endif // PLAYER_H