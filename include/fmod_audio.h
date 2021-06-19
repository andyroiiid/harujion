//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_FMOD_AUDIO_H
#define HARUJION_FMOD_AUDIO_H

#include <string>
#include <fmod_studio.hpp>
#include <sol/sol.hpp>

#include "non_copyable.h"
#include "physfs.h"

class FmodAudio {
public:
    static FmodAudio &getInstance();

    void update();

    void bindFunctions(sol::table &haru);

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
    FMOD::Studio::Bus *bus = nullptr;
};

#endif //HARUJION_FMOD_AUDIO_H
