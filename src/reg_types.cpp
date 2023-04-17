#include "reg_types.hpp"

#include <gdextension_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "player.hpp"
#include "mob.hpp"
#include "main.hpp"
#include "hud.hpp"
#include "exports_node.hpp"

using namespace godot;

void init_mod(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;

    ClassDB::register_class<Player>();
    ClassDB::register_class<Mob>();
    ClassDB::register_class<HUD>();
    ClassDB::register_class<Main>();
    ClassDB::register_class<ExportsNode>();
}

void uninit_mod(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
}

extern "C"
{
    GDExtensionBool GDE_EXPORT lib_init(const GDExtensionInterface *p_interface, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
    {
        GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

        init_obj.register_initializer(init_mod);
        init_obj.register_terminator(uninit_mod);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}