# harujion

a lua 2d game engine (or framework?)

## Dependencies

- [fmod](https://fmod.com/) (Please install FMOD Studio API Windows)
- [glad](https://github.com/Dav1dde/glad/tree/glad2) (Version 2, source included)
- [glfw](https://github.com/glfw/glfw) (Git submodule)
- [glm](https://github.com/g-truc/glm) (Git submodule)
- [imgui](https://github.com/ocornut/imgui) (Source included but not used yet)
- [luajit](https://luajit.org/) (Headers and prebuilt binaries included, 64bit msvc only)
- [physfs](https://www.icculus.org/physfs/) (Git submodule)
- [sol2](https://github.com/ThePhD/sol2) (Source included)
- [spdlog](https://github.com/gabime/spdlog) (Git submodule)
- [stb](https://github.com/nothings/stb) (Source included)

## Build Instructions

1. Clone with `git clone --recursive https://github.com/andyroiiid/harujion.git`
2. You should be able to build the project with cmake.
3. The built files are in the `out` directory under your CMake build directory.

## Sample Game

Two samples are included in the `samples` folder.

Replace the content of `assets` folder with a sample to test it.

Run the engine executable to play the game.
