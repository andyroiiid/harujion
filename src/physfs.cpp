//
// Created by andyroiiid on 6/13/2021.
//

#include "physfs.h"

#include <spdlog/spdlog.h>
#include <sol/sol.hpp>

#include "../dependencies//physfs/src/physfs.h"

Physfs &Physfs::getInstance() {
    static Physfs instance;
    return instance;
}

Physfs::Physfs() {
    if (!PHYSFS_init(__argv[0])) {
        spdlog::error("failed to init physfs: {}", PHYSFS_getLastError());
    } else {
        PHYSFS_Version version;
        PHYSFS_getLinkedVersion(&version);
        spdlog::info("physfs {}.{}.{} init", version.major, version.minor, version.patch);

        mount("assets", "/");
    }
}

Physfs::~Physfs() {
    if (!PHYSFS_deinit()) {
        spdlog::error("failed to destroy physfs: {}", PHYSFS_getLastError());
    }
}

Physfs &Physfs::mount(const std::string &newDir, const std::string &mountPoint, bool appendToPath) {
    if (!PHYSFS_mount(newDir.c_str(), mountPoint.c_str(), appendToPath)) {
        spdlog::error("physfs failed to mount {} at {}: {}", newDir, mountPoint, PHYSFS_getLastError());
    } else {
        spdlog::info("physfs mount {} at {}", newDir, mountPoint);
    }
    return *this;
}

std::string Physfs::readFile(const std::string &filename) { // NOLINT(readability-convert-member-functions-to-static)
    PHYSFS_File *file = PHYSFS_openRead(filename.c_str());
    if (!file) {
        spdlog::error("physfs failed to open file {}: {}", filename, PHYSFS_getLastError());
        return std::string();
    }
    PHYSFS_sint64 length = PHYSFS_fileLength(file);
    if (length == 01) {
        spdlog::error("physfs failed to get file size {}: {}", filename, PHYSFS_getLastError());
        return std::string();
    }
    std::string bytes(length, '\0');
    if (PHYSFS_readBytes(file, bytes.data(), length) == -1) {
        spdlog::error("physfs failed to read file {}: {}", filename, PHYSFS_getLastError());
    }
    return bytes;
}

int Physfs::luaPackageLoader(lua_State *L) {
    std::string path = sol::stack::get<std::string>(L, 1);
    spdlog::info("physfs loading lua package: {}", path);
    std::string script = getInstance().readFile(path);
    luaL_loadbuffer(L, script.data(), script.size(), path.c_str());
    return 1;
}
