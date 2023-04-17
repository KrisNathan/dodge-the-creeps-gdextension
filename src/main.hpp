#ifndef MAIN_H
#define MAIN_H

#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/path_follow2d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/godot.hpp>

#include "hud.hpp"
#include "player.hpp"
#include "is_editor.hpp"

class Main : public godot::Node {
  GDCLASS(Main, godot::Node);

private:
  int score;
  HUD *_hud;
  Player *_player;
  godot::Node2D *_start_position;
  godot::PathFollow2D *_mob_spawn_location;
  godot::Timer *_mob_timer;
  godot::Timer *_score_timer;
  godot::Timer *_start_timer;

  godot::AudioStreamPlayer *_music;
  godot::AudioStreamPlayer *_death_sound;
  godot::Ref<godot::RandomNumberGenerator> _random;

protected:
  static void _bind_methods();

public:
  godot::Ref<godot::PackedScene> mob_scene;

  void _init() {}
  void _ready();
  void game_over();
  void new_game();
  void on_MobTimer_timeout();
  void on_ScoreTimer_timeout();
  void on_StartTimer_timeout();
  void set_mob_scene(godot::Ref<godot::PackedScene> mob_scene);
  godot::Ref<godot::PackedScene> get_mob_scene();
};

#endif // MAIN_H
