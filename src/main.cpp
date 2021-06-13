#include "engine.h"

int main() {
    auto &engine = Engine::getInstance();
    engine.mainLoop();
    return 0;
}
