#ifndef HUD_H
#define HUD_H

#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/timer.hpp>

class HUD : public godot::CanvasLayer
{
    GDCLASS(HUD, godot::CanvasLayer);

private:
    godot::Label *_score_label;
    godot::Label *_message_label;
    godot::Timer *_start_message_timer;
    godot::Timer *_get_ready_message_timer;
    godot::Button *_start_button;
    godot::Timer *_start_button_timer;

protected:
    static void _bind_methods();

public:
    void _init() {}
    void _ready();
    void show_get_ready();
    void show_game_over();
    void update_score(const int score);
    void _on_StartButton_pressed();
    void _on_StartMessageTimer_timeout();
    void _on_GetReadyMessageTimer_timeout();
    void _on_StartButtonTimer_timeout();
};

#endif // HUD_H