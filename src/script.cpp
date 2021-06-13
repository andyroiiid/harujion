//
// Created by andyroiiid on 6/13/2021.
//

#include "script.h"

#include <spdlog/spdlog.h>

Script &Script::getInstance() {
    static Script instance;
    return instance;
}

Script::Script() {
    L.open_libraries(sol::lib::base, sol::lib::package);
    L.add_package_loader(Physfs::luaPackageLoader);
}

void Script::script(const std::string &code) {
    auto result = L.script(code);
    if (!result.valid()) {
        sol::error error = result;
        spdlog::error("lua error: {}", error.what());
    }
}
