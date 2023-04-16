#include "player.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

void Player::_bind_methods()
{
    // godot::ClassDB::bind_method(godot::D_METHOD("get_animated_sprite"), &Player::get_animated_sprite);
    // godot::ClassDB::bind_method(godot::D_METHOD("set_animated_sprite", "animated_sprite"), &Player::set_animated_sprite);
    // godot::ClassDB::bind_method(godot::D_METHOD("get_collision_shape"), &Player::get_collision_shape);
    // godot::ClassDB::bind_method(godot::D_METHOD("set_collision_shape", "collision_shape"), &Player::set_collision_shape);

    // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "animated_sprite", godot::PROPERTY_HINT_NODE_TYPE, "AnimatedSprite2D"), "set_animated_sprite", "get_animated_sprite");
    // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "collision_shape", godot::PROPERTY_HINT_NODE_TYPE, "CollisionShape2D"), "set_collision_shape", "get_collision_shape");
}

void Player::_ready()
{
    if (godot::Engine::get_singleton()->is_editor_hint())
        return;

    animated_sprite = get_node<godot::AnimatedSprite2D>("AnimatedSprite2D");
    collision_shape = get_node<godot::CollisionShape2D>("CollisionShape2D");
    _input_object = godot::Input::get_singleton();
    _screen_size = get_viewport_rect().size;

    hide();
}

void Player::_process(const double p_delta)
{
    if (godot::Engine::get_singleton()->is_editor_hint())
        return;
        
    godot::Vector2 velocity(0, 0);

    velocity.x = _input_object->get_action_strength("move_right") - _input_object->get_action_strength("move_left");
    velocity.y = _input_object->get_action_strength("move_down") - _input_object->get_action_strength("move_up");

    if (velocity.length() > 0)
    {
        velocity = velocity.normalized() * speed;
        animated_sprite->play();
    }
    else
    {
        animated_sprite->stop();
    }

    godot::Vector2 position = get_position();
    position += velocity * (real_t)p_delta;
    position.x = godot::Math::clamp(position.x, (real_t)0.0, _screen_size.x);
    position.y = godot::Math::clamp(position.y, (real_t)0.0, _screen_size.y);
    set_position(position);

    if (velocity.x != 0)
    {
        animated_sprite->set_animation("walk");
        animated_sprite->set_flip_v(false);
        // See the note below about boolean assignment.
        animated_sprite->set_flip_h(velocity.x < 0);
    }
    else if (velocity.y != 0)
    {
        animated_sprite->set_animation("up");
        animated_sprite->set_flip_v(velocity.y > 0);
    }
}

void Player::_on_body_entered(godot::Node2D *_body)
{
    if (godot::Engine::get_singleton()->is_editor_hint())
        return;

    hide(); // Player disappears after being hit.
    // emit_signal("hit");
    // // Must be deferred as we can't change physics properties on a physics callback.
    // collision_shape->set_deferred("disabled", true);
}

void Player::start(const godot::Vector2 p_position)
{
    set_position(p_position);
    show();
    collision_shape->set_disabled(false);
}

void Player::set_collision_shape(godot::CollisionShape2D *new_collision_shape)
{
    collision_shape = new_collision_shape;
};

godot::CollisionShape2D *Player::get_collision_shape()
{
    return collision_shape;
};

void Player::set_animated_sprite(godot::AnimatedSprite2D
                                     *new_animated_sprite)
{
    animated_sprite = new_animated_sprite;
};

godot::AnimatedSprite2D *Player::get_animated_sprite()
{
    return animated_sprite;
};