#ifndef MOB_H
#define MOB_H

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/rigid_body2d.hpp>

class Mob : public godot::RigidBody2D
{
    GDCLASS(Mob, godot::RigidBody2D);

    godot::AnimatedSprite2D *_animated_sprite;

protected:
    static void _bind_methods();

public:
    void _init() {}
    void _ready();
    void _on_VisibleOnScreenNotifier2D_screen_exited();
};

#endif // MOB_H