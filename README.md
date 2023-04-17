# Dodge The Creeps GDExtension

Dodge The Creeps but written with GDExtension

## Building

### Prerequisites 

- Godot Engine with PR:  https://github.com/godotengine/godot/pull/75758
- SCons
- C++ compiler (msvc, mingw gcc, llvm)

### Pulling The Submodules

```sh
git submodule update --init
```

### Building

```sh
scons platform=<yourplatform here> use_mingw=<yesno> use_llvm=<yesno> -j<amount of processors>
```