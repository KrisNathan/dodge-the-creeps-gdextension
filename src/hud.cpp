#include "hud.hpp"

#include <cstdio>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void HUD::_ready() {
  if (godot::Engine::get_singleton()->is_editor_hint())
    return;

  _score_label = get_node<godot::Label>("ScoreLabel");
  _message_label = get_node<godot::Label>("MessageLabel");
  _start_message_timer = get_node<godot::Timer>("StartMessageTimer");
  _get_ready_message_timer = get_node<godot::Timer>("GetReadyMessageTimer");
  _start_button = get_node<godot::Button>("StartButton");
  _start_button_timer = get_node<godot::Timer>("StartButtonTimer");

  _start_button->connect("pressed",
                         godot::Callable(this, "_on_StartButton_pressed"));
  _start_message_timer->connect(
      "timeout", godot::Callable(this, "_on_StartMessageTimer_timeout"));
  _get_ready_message_timer->connect(
      "timeout", godot::Callable(this, "_on_GetReadyMessageTimer_timeout"));
  _start_button_timer->connect(
      "timeout", godot::Callable(this, "_on_StartButtonTimer_timeout"));
}

void HUD::show_get_ready() {
  _message_label->set_text("Get Ready");
  _message_label->show();
  _get_ready_message_timer->start();
}

void HUD::show_game_over() {
  _message_label->set_text("Game Over");
  _message_label->show();
  _start_message_timer->start();
}

void HUD::update_score(const int p_score) {
  _score_label->set_text(godot::Variant(p_score)); // PROBLEMATIC
  // https://github.com/godotengine/godot/issues/75757
  // char str[32];
  // std::snprintf(str, 16, "%d", p_score);
  // _score_label->set_text(str);
}

void HUD::_on_StartButton_pressed() {
  _start_button->hide();
  emit_signal("start_game");
}

void HUD::_on_StartMessageTimer_timeout() {
  _message_label->set_text("Dodge the\nCreeps");
  _message_label->show();
  _start_button_timer->start();
}

void HUD::_on_StartButtonTimer_timeout() { _start_button->show(); }

void HUD::_on_GetReadyMessageTimer_timeout() { _message_label->hide(); }

void HUD::_bind_methods() {
  // godot::ClassDB::bind_method(godot::D_METHOD("_ready"), &HUD::_ready);
  godot::ClassDB::bind_method(godot::D_METHOD("show_get_ready"),
                              &HUD::show_get_ready);
  godot::ClassDB::bind_method(godot::D_METHOD("show_game_over"),
                              &HUD::show_game_over);
  godot::ClassDB::bind_method(godot::D_METHOD("update_score", "score"),
                              &HUD::update_score);
  godot::ClassDB::bind_method(godot::D_METHOD("_on_StartButton_pressed"),
                              &HUD::_on_StartButton_pressed);
  godot::ClassDB::bind_method(godot::D_METHOD("_on_StartMessageTimer_timeout"),
                              &HUD::_on_StartMessageTimer_timeout);
  godot::ClassDB::bind_method(godot::D_METHOD("_on_StartButtonTimer_timeout"),
                              &HUD::_on_StartButtonTimer_timeout);
  godot::ClassDB::bind_method(
      godot::D_METHOD("_on_GetReadyMessageTimer_timeout"),
      &HUD::_on_GetReadyMessageTimer_timeout);
  ADD_SIGNAL(godot::MethodInfo("start_game"));

  // ADD_SIGNAL(MethodInfo("custom_signal", PropertyInfo(Variant::STRING,
  // "name"), PropertyInfo(Variant::INT, "value")));

  // godot::register_method("_ready", &HUD::_ready);
  // godot::register_method("show_get_ready", &HUD::show_get_ready);
  // godot::register_method("show_game_over", &HUD::show_game_over);
  // godot::register_method("update_score", &HUD::update_score);
  // godot::register_method("_on_StartButton_pressed",
  // &HUD::_on_StartButton_pressed);
  // godot::register_method("_on_StartMessageTimer_timeout",
  // &HUD::_on_StartMessageTimer_timeout);
  // godot::register_method("_on_GetReadyMessageTimer_timeout",
  // &HUD::_on_GetReadyMessageTimer_timeout);
  // godot::register_signal<HUD>("start_game", godot::Dictionary());
}