#include "main.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

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

  ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "mob_scene",
                                   godot::PROPERTY_HINT_RESOURCE_TYPE,
                                   "PackedScene"),
               "set_mob_scene", "get_mob_scene");
}

void Main::_ready() {
  if (IS_EDITOR())
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
}

void Main::on_StartTimer_timeout() {
  _mob_timer->start();
  _score_timer->start();
}

void Main::on_MobTimer_timeout() {
  // Create a new instance of the Mob scene.
  godot::Node *mob = mob_scene->instantiate();

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
