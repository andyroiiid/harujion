//
// Created by andyroiiid on 6/14/2021.
//

#include "fmod_audio.h"

#include <spdlog/spdlog.h>
#include <fmod_errors.h>

using namespace FMOD::Studio;

FmodAudio &FmodAudio::getInstance() {
    static FmodAudio instance;
    return instance;
}

void FmodAudio::checkFmod(FMOD_RESULT result, const std::string &failMessage) {
    if (result == FMOD_OK) return;

    spdlog::error("{}: {}", failMessage, FMOD_ErrorString(result));
}

FmodAudio::FmodAudio() {
    checkFmod(System::create(&system), "failed to create fmod system");
    if (system == nullptr) {
        exit(EXIT_FAILURE);
    }
    int product = FMOD_VERSION >> 16;
    int major = (FMOD_VERSION >> 8) & 0xFF;
    int minor = FMOD_VERSION & 0xFF;
    spdlog::info("fmod version {:x}.{:02x}.{:02x} created", product, major, minor);
    checkFmod(system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr),
              "failed to initialize fmod system");
    loadBank("Master.bank");
    loadBank("Master.strings.bank");
    checkFmod(system->getBus("bus:/", &bus), "failed to get master bus");
}

FmodAudio::~FmodAudio() {
    checkFmod(system->unloadAll(), "failed to unload all banks");
    checkFmod(system->release(), "failed to release fmod system");
}

void FmodAudio::update() {
    checkFmod(system->update(), "failed to update fmod system");
}

sol::table FmodAudio::getLuaTable(sol::state &lua) {
    sol::table table = lua.create_table();
    table.set_function("loadBank", [this](const std::string &filename) { loadBank(filename); });
    table.set_function("setVolume", [this](float volume) { setVolume(volume); });
    table.set_function(
            "getEventDescription",
            [this](const std::string &eventPath) { return getEventDescription(eventPath); }
    );
    table.set_function("fireOneShotEvent", &FmodAudio::fireOneShotEvent);
    return table;
}

void FmodAudio::loadBank(const std::string &filename) {
    spdlog::info("loading bank {}", filename);
    auto bytes = physfs.readFile(filename);
    Bank *bank = nullptr;
    FMOD_RESULT result = system->loadBankMemory(
            bytes.data(),
            static_cast<int>(bytes.size()),
            FMOD_STUDIO_LOAD_MEMORY,
            FMOD_STUDIO_LOAD_BANK_NORMAL,
            &bank
    );
    if (result != FMOD_OK) {
        spdlog::error("failed to load bank {}: {}", filename, FMOD_ErrorString(result));
    }
}

void FmodAudio::setVolume(float volume) {
    checkFmod(bus->setVolume(volume), "failed to set master bus volume");
}

FMOD::Studio::EventDescription *FmodAudio::getEventDescription(const std::string &eventPath) {
    EventDescription *eventDescription = nullptr;
    FMOD_RESULT result = system->getEvent(eventPath.c_str(), &eventDescription);
    if (result != FMOD_OK) {
        spdlog::error("failed to get fmod event {}: {}", eventPath, FMOD_ErrorString(result));
        return nullptr;
    } else {
        return eventDescription;
    }
}

void FmodAudio::fireOneShotEvent(FMOD::Studio::EventDescription *eventDescription) {
    EventInstance *eventInstance = nullptr;
    checkFmod(eventDescription->createInstance(&eventInstance), "failed to create fmod event instance");
    if (eventInstance == nullptr) {
        return;
    }
    checkFmod(eventInstance->start(), "failed to start fmod event");
    checkFmod(eventInstance->release(), "failed to release fmod event");
}
