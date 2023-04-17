#include "main.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "mob.hpp"

void Main::_bind_methods() {
  // godot::ClassDB::bind_method(godot::D_METHOD("_ready"), &Main::_ready);
  godot::ClassDB::bind_method(godot::D_METHOD("game_over"), &Main::game_over);
  godot::ClassDB::bind_method(godot::D_METHOD("new_game"), &Main::new_game);
  godot::ClassDB::bind_method(godot::D_METHOD("on_MobTimer_timeout"),
                              &Main::on_MobTimer_timeout);
  godot::ClassDB::bind_method(godot::D_METHOD("on_ScoreTimer_timeout"),
                              &Main::on_ScoreTimer_timeout);
  godot::ClassDB::bind_method(godot::D_METHOD("on_StartTimer_timeout"),
                              &Main::on_StartTimer_timeout);

  godot::ClassDB::bind_method(godot::D_METHOD("set_mob_scene", "mob_scene"),
                              &Main::set_mob_scene);
  godot::ClassDB::bind_method(godot::D_METHOD("get_mob_scene"),
                              &Main::get_mob_scene);
  godot::ClassDB::bind_method(godot::D_METHOD("set_hud", "hud"),
                              &Main::set_hud);
  godot::ClassDB::bind_method(godot::D_METHOD("get_hud"), &Main::get_hud);
  godot::ClassDB::bind_method(godot::D_METHOD("set_player", "player"),
                              &Main::set_player);
  godot::ClassDB::bind_method(godot::D_METHOD("get_player"), &Main::get_player);
  godot::ClassDB::bind_method(
      godot::D_METHOD("set_start_position", "start_position"),
      &Main::set_start_position);
  godot::ClassDB::bind_method(godot::D_METHOD("get_start_position"),
                              &Main::get_start_position);
  godot::ClassDB::bind_method(
      godot::D_METHOD("set_mob_spawn_location", "mob_spawn_location"),
      &Main::set_mob_spawn_location);
  godot::ClassDB::bind_method(godot::D_METHOD("get_mob_spawn_location"),
                              &Main::get_mob_spawn_location);
  godot::ClassDB::bind_method(godot::D_METHOD("set_mob_timer", "mob_timer"),
                              &Main::set_mob_timer);
  godot::ClassDB::bind_method(godot::D_METHOD("get_mob_timer"),
                              &Main::get_mob_timer);
  godot::ClassDB::bind_method(godot::D_METHOD("set_score_timer", "score_timer"),
                              &Main::set_score_timer);
  godot::ClassDB::bind_method(godot::D_METHOD("get_score_timer"),
                              &Main::get_score_timer);
  godot::ClassDB::bind_method(godot::D_METHOD("set_start_timer", "start_timer"),
                              &Main::set_start_timer);
  godot::ClassDB::bind_method(godot::D_METHOD("get_start_timer"),
                              &Main::get_start_timer);

  ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "mob_scene",
                                   godot::PROPERTY_HINT_RESOURCE_TYPE,
                                   "PackedScene"),
               "set_mob_scene", "get_mob_scene");

  // PROBLEMATIC: Variants crash everything!
  // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "hud",
  // godot::PROPERTY_HINT_NODE_TYPE, "CanvasLayer"), "set_hud", "get_hud");
  // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "player",
  // godot::PROPERTY_HINT_NODE_TYPE, "Area2D"), "set_player", "get_player");
  // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "start_position",
  // godot::PROPERTY_HINT_NODE_TYPE, "Node2D"), "set_start_position",
  // "get_start_position");
  // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT,
  // "mob_spawn_location", godot::PROPERTY_HINT_NODE_TYPE, "PathFollow2D"),
  // "set_mob_spawn_location", "get_mob_spawn_location");
  // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "mob_timer",
  // godot::PROPERTY_HINT_NODE_TYPE, "Timer"), "set_mob_timer",
  // "get_mob_timer"); ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT,
  // "score_timer", godot::PROPERTY_HINT_NODE_TYPE, "Timer"), "set_score_timer",
  // "get_score_timer");
  // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "start_timer",
  // godot::PROPERTY_HINT_NODE_TYPE, "Timer"), "set_start_timer",
  // "get_start_timer");
}

void Main::_ready() {
  godot::UtilityFunctions::print("Main::_ready");
  if (godot::Engine::get_singleton()->is_editor_hint())
    return;

  _hud = get_node<HUD>("HUD");
  _player = get_node<Player>("Player");
  _start_position = get_node<godot::Node2D>("StartPosition");
  _mob_spawn_location =
      get_node<godot::PathFollow2D>("MobPath/MobSpawnLocation");
  _mob_timer = get_node<godot::Timer>("MobTimer");
  _score_timer = get_node<godot::Timer>("ScoreTimer");
  _start_timer = get_node<godot::Timer>("StartTimer");

  // Uncomment these after adding the nodes in the "Sound effects" section of
  // "Finishing up".
  //_music = get_node<godot::AudioStreamPlayer>("Music");
  //_death_sound = get_node<godot::AudioStreamPlayer>("DeathSound");

  godot::Ref<godot::RandomNumberGenerator> rng(
      memnew(godot::RandomNumberGenerator));
  _random = rng;

  _hud->connect("start_game", godot::Callable(this, "new_game"));
  _mob_timer->connect("timeout", godot::Callable(this, "on_MobTimer_timeout"));
  _score_timer->connect("timeout",
                        godot::Callable(this, "on_ScoreTimer_timeout"));
  _start_timer->connect("timeout",
                        godot::Callable(this, "on_StartTimer_timeout"));
  _player->connect("hit", godot::Callable(this, "game_over"));
  // new_game();
}

void Main::game_over() {
  _score_timer->stop();
  _mob_timer->stop();
  _hud->show_game_over();
}

void Main::new_game() {
  score = 0;
  _player->start(_start_position->get_position());
  _start_timer->start();
  _hud->update_score(score);
  _hud->show_get_ready();
  get_tree()->call_group("mobs", "queue_free");
}

void Main::on_ScoreTimer_timeout() {
  score += 1;
  _hud->update_score(score);
  godot::UtilityFunctions::print("on_ScoreTimer_timeout");
}

void Main::on_StartTimer_timeout() {
  _mob_timer->start();
  _score_timer->start();
  godot::UtilityFunctions::print("on_StartTimer_timeout");
}

#include <cstdio>

void Main::on_MobTimer_timeout() {
  godot::UtilityFunctions::print("on_MobTimer_timeout");

  // Create a new instance of the Mob scene.
  godot::Node *mob = mob_scene->instantiate();

  // godot::UtilityFunctions::print(_random);

  // Choose a random location on Path2D.
  _mob_spawn_location->set_progress_ratio(_random->randf());

  // Set the mob's direction perpendicular to the path direction.
  double direction = _mob_spawn_location->get_rotation() + (double)Math_PI / 2;

  // Set the mob's position to a random location.
  mob->set("position", _mob_spawn_location->get_position());

  // Add some randomness to the direction.
  direction += _random->randf_range((double)-Math_PI / 4, (double)Math_PI / 4);
  mob->set("rotation", direction);

  // Choose the velocity for the mob.
  godot::Vector2 velocity =
      godot::Vector2(_random->randf_range(150.0, 250.0), 0.0);
  mob->set("linear_velocity", velocity.rotated(direction));

  // Spawn the mob by adding it to the Main scene. PROBLEMATIC
  add_child(mob);
}

void Main::set_mob_scene(godot::Ref<godot::PackedScene> new_mob_scene) {
  mob_scene = new_mob_scene;
}

godot::Ref<godot::PackedScene> Main::get_mob_scene() { return mob_scene; }

void Main::set_hud(HUD *hud) { _hud = hud; };
HUD *Main::get_hud() { return _hud; };
void Main::set_player(Player *player) { _player = player; };
Player *Main::get_player() { return _player; };
void Main::set_start_position(godot::Node2D *start_position) {
  _start_position = start_position;
};
godot::Node2D *Main::get_start_position() { return _start_position; };
void Main::set_mob_spawn_location(godot::PathFollow2D *mob_spawn_location) {
  _mob_spawn_location = mob_spawn_location;
};
godot::PathFollow2D *Main::get_mob_spawn_location() {
  return _mob_spawn_location;
};
void Main::set_mob_timer(godot::Timer *mob_timer) { _mob_timer = mob_timer; };
godot::Timer *Main::get_mob_timer() { return _mob_timer; };
void Main::set_score_timer(godot::Timer *score_timer) {
  _score_timer = score_timer;
};
godot::Timer *Main::get_score_timer() { return _score_timer; };
void Main::set_start_timer(godot::Timer *start_timer) {
  _start_timer = start_timer;
};
godot::Timer *Main::get_start_timer() { return _start_timer; };