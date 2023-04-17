#include "mob.hpp"

#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/visible_on_screen_notifier2d.hpp>

void Mob::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("on_VisibleOnScreenNotifier2D_screen_exited"), &Mob::on_VisibleOnScreenNotifier2D_screen_exited);
}

void Mob::_ready() {
    if (IS_EDITOR())
        return;
    
    godot::Ref<godot::RandomNumberGenerator> random(memnew(godot::RandomNumberGenerator));
    _animated_sprite = get_node<godot::AnimatedSprite2D>("AnimatedSprite2D");

    godot::PackedStringArray mob_types = _animated_sprite->get_sprite_frames()->get_animation_names();
    _animated_sprite->play(mob_types[random->randi() % mob_types.size()]);

    godot::VisibleOnScreenNotifier2D *vos_notif = get_node<godot::VisibleOnScreenNotifier2D>("VisibleOnScreenNotifier2D");
    vos_notif->connect("screen_exited", godot::Callable(this, "on_VisibleOnScreenNotifier2D_screen_exited"));

    add_to_group("mobs");
}

void Mob::on_VisibleOnScreenNotifier2D_screen_exited() {
    queue_free();
}