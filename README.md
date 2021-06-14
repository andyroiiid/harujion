# harujion

a lua 2d game engine (or framework?)

## Dependencies

- [glad](https://github.com/Dav1dde/glad/tree/glad2) (version 2, source included)
- [glfw](https://github.com/glfw/glfw)
- [glm](https://github.com/g-truc/glm)
- [imgui](https://github.com/ocornut/imgui) (source included but not used yet)
- [lua](http://www.lua.org/home.html) (source included)
- [physfs](https://www.icculus.org/physfs/)
- [sol2](https://github.com/ThePhD/sol2) (source included)
- [spdlog](https://github.com/gabime/spdlog)
- [stb](https://github.com/nothings/stb) (source included)

## Build Instructions

1. Download the release source code from [glfw](https://github.com/glfw/glfw), [glm](https://github.com/g-truc/glm), [physfs](https://www.icculus.org/physfs/), [spdlog](https://github.com/gabime/spdlog).
2. Extract them to the `dependencies` folder.
   - harujion
     - assets
     - dependencies
       - glad
       - **glfw**
         - CMakeLists.txt
         - ...
       - **glm**
         - CMakeLists.txt
         - ...
       - imgui
       - lua
       - **physfs**
         - CMakeLists.txt
         - ...
       - sol2
       - **spdlog**
         - CMakeLists.txt
         - ...
       - stb
     - include
     - src
     - ...
3. You should be able to build the project with cmake.

> Here is a link to [the CMake official tutorial.](https://cmake.org/cmake/help/latest/guide/tutorial/index.html#build-and-test)

## Sample Game

A sample game (flappy bird) is included in the `assets` folder.

Run the engine excutable from the project root directory to play the game.
