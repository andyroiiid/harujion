//
// Created by andyroiiid on 6/13/2021.
//

#ifndef HARUJION_SCRIPT_H
#define HARUJION_SCRIPT_H

#include <sol/sol.hpp>

#include "non_copyable.h"
#include "physfs.h"

class Script {
public:
    static Script &getInstance();

    void script(const std::string &code);

    inline void scriptFile(const std::string &filename) {
        return script(physfs.readFile(filename));
    }

private:
    Script();

    Physfs &physfs = Physfs::getInstance();

    sol::state L;
};

#endif //HARUJION_SCRIPT_H
