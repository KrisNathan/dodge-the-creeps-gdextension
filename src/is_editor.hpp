#include <godot_cpp/classes/engine.hpp>

#define IS_EDITOR() godot::Engine::get_singleton()->is_editor_hint()
