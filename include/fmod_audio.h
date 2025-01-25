// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include <fmod_studio.hpp>
#include <string>

#include "physfs.h"

class FmodAudio
{
public:
    static FmodAudio &getInstance();

    void update();

    void loadBank(const std::string &filename);

    void setVolume(float volume);

    FMOD::Studio::EventDescription *getEventDescription(const std::string &eventPath);

    static void fireOneShotEvent(FMOD::Studio::EventDescription *eventDescription);

private:
    FmodAudio();

    ~FmodAudio();

    static void checkFmod(FMOD_RESULT result, const std::string &failMessage);

    Physfs &physfs = Physfs::getInstance();

    FMOD::Studio::System *system = nullptr;
    FMOD::Studio::Bus    *bus    = nullptr;
};
