//
// Created by Josi on 08.08.2024.
//

#include <iostream>
#include "SoundHandler.h"
#include "Store.h"

SoundHandler::SoundHandler()
{
    //todo: add bool currentlyPlaying / loop ambient

   soundMap[EXPLOSION] = LoadSound("assets/audio/sfx/sfx_explosion.wav");
    soundMap[IMPACT_FLOOR] = LoadSound("assets/audio/sfx/sfx_impact_floor.wav");
    soundMap[IMPACT_WATER] = LoadSound("assets/audio/sfx/sfx_impact_water.wav");
    soundMap[NOTE] = LoadSound("assets/audio/sfx/sfx_lore.wav");
    soundMap[PUSH] = LoadSound("assets/audio/sfx/sfx_push.wav");
    soundMap[RESPAWN_ACTIVATE] = LoadSound("assets/audio/sfx/sfx_respawnpoint_activate.wav");
    soundMap[RESPAWN_REACTIVATE] = LoadSound("assets/audio/sfx/sfx_respawnpoint_reactivate.wav");
    soundMap[RUBBLE] = LoadSound("assets/audio/sfx/sfx_rubble_remove.wav");
    soundMap[SHOT] = LoadSound("assets/audio/sfx/sfx_shot_pistol.wav");

}

void SoundHandler::playSound(SoundEnum pa_sound )
{
    if (pa_sound < soundMap.size() && pa_sound != AMBIENT_UNDERWORLD && pa_sound != AMBIENT_OVERWORLD)
    {
        PlaySound(soundMap[pa_sound]);
    }
}

void SoundHandler::update()
{


}
