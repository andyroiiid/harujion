#include "physfs.h"
#include "script.h"
#include "window.h"

int main() {
    auto &physfs = Physfs::getInstance();
    physfs.mount("assets", "/");

    auto &script = Script::getInstance();
    script.scriptFile("main.lua");

    auto &window = Window::getInstance();
    while (!window.shouldClose()) {
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}
