//
// Created by Josi on 08.08.2024.
//

#ifndef HIVE_SOUNDHANDLER_H
#define HIVE_SOUNDHANDLER_H


#include <map>
#include <vector>
#include "raylib.h"

class SoundHandler
{
public:
    enum SoundEnum
    {
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
    SoundHandler();
    void playSound(SoundEnum pa_sound);
    void playAmbient(SoundEnum pa_ambient);
    void update();
protected:
    std::map<int, Sound> soundMap;
    Music currentAmbient;
    Music overworldAmbient;
    Music underworldAmbient;
};


#endif //HIVE_SOUNDHANDLER_H
