//
// Created by andyroiiid on 6/13/2021.
//

#ifndef HARUJION_PHYSFS_H
#define HARUJION_PHYSFS_H

#include <string>

#include "non_copyable.h"

struct lua_State;

class Physfs : NonCopyable {
public:
    static Physfs &getInstance();

    Physfs &mount(const std::string &newDir, const std::string &mountPoint, bool appendToPath = true);

    std::string readFile(const std::string &filename);

    static int luaPackageLoader(lua_State *L);

private:
    Physfs();

    ~Physfs();
};

#endif //HARUJION_PHYSFS_H
