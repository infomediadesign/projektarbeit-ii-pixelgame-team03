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
            AMBIENT_OVERWORLD,
            AMBIENT_UNDERWORLD,

            EXPLOSION,
            IMPACT_FLOOR,
            IMPACT_WATER,
            NOTE,
            PUSH,
            RESPAWN_ACTIVATE,
            RESPAWN_REACTIVATE,
            RUBBLE,
            SHOT,
        };

        static SoundHandler &getInstance();

        SoundHandler();

        void playSound(SoundEnum pa_sound);

        void playAmbient(SoundEnum pa_ambient);

        void update();

    protected:
        std::map<int, Sound> soundMap_;
        std::map<int, Music> ambientMap_;

        SoundEnum currentAmbient_;
        static std::mutex soundHandler_mutex_;
    };
}

#endif //HIVE_SOUNDHANDLER_H
