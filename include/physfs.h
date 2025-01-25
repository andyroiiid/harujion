// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include <string>

#include "non_copyable.h"

struct lua_State;

class Physfs : NonCopyable
{
public:
    static Physfs &getInstance();

    Physfs &mount(const std::string &newDir, const std::string &mountPoint, bool appendToPath = true);

    std::string readFile(const std::string &filename);

    static int luaPackageLoader(lua_State *L);

private:
    Physfs();

    ~Physfs();
};
