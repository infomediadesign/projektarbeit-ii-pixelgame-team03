//
// Created by Josi on 08.08.2024.
//

#ifndef HIVE_SOUNDHANDLER_H
#define HIVE_SOUNDHANDLER_H


#include <map>
#include <vector>
#include "raylib.h"

namespace CoreLogic::EventManagement
{
    class SoundHandler
    {
    public:
        enum SoundEnum
        {
            //ambient music has to be written before sfx / have a smaller numeber
            AMBIENT_UNDERWORLD = 0,
            AMBIENT_OVERWORLD = 1,

            EXPLOSION,
            IMPACT_FLOOR,
            IMPACT_WATER,
            NOTE,
            PUSH,
            RESPAWN_ACTIVATE,
            RESPAWN_REACTIVATE,
            RUBBLE,
            SHOT,
            BELL,
            DEATH_DRONE,
            DEATH_HUMAN,

        };

        static SoundHandler &getInstance();

        SoundHandler();

        void playSound(SoundEnum pa_sound);

        void playAmbient(SoundEnum pa_ambient);

        void update();

    protected:
        std::map<int, std::pair<Sound, float>> soundMap_;
        std::map<int, std::pair<Music, float>> ambientMap_;

        SoundEnum currentAmbient_;
        static std::mutex soundHandler_mutex_;
    };
}

#endif //HIVE_SOUNDHANDLER_H
