#include "mob.hpp"

#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/engine.hpp>

void Mob::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("_on_VisibleOnScreenNotifier2D_screen_exited"), &Mob::_on_VisibleOnScreenNotifier2D_screen_exited);
}

void Mob::_ready() {
    if (godot::Engine::get_singleton()->is_editor_hint())
        return;
        
    godot::Ref<godot::RandomNumberGenerator> random;
    _animated_sprite = get_node<godot::AnimatedSprite2D>("AnimatedSprite2D");

    godot::PackedStringArray mob_types = _animated_sprite->get_sprite_frames()->get_animation_names();
    _animated_sprite->play(mob_types[random->randi() % mob_types.size()]);
}

void Mob::_on_VisibleOnScreenNotifier2D_screen_exited() {
    if (godot::Engine::get_singleton()->is_editor_hint())
        return;
    
    queue_free();
}