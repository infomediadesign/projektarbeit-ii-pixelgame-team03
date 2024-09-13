//
// Created by Josi on 08.08.2024.
//

#include <iostream>
#include <mutex>
#include "SoundHandler.h"
#include "DesignConfig.h"

namespace CoreLogic::EventManagement
{

    std::mutex SoundHandler::soundHandler_mutex_;

    SoundHandler::SoundHandler()
    {
        //todo: add bool currentlyPlaying / loop ambient
        ambientMap_[AMBIENT_OVERWORLD] = LoadMusicStream("assets/audio/tracks/oberwelt_amb.wav");
        ambientMap_[AMBIENT_UNDERWORLD] = LoadMusicStream("assets/audio/tracks/unterwelt_amb.wav");

        soundMap_[EXPLOSION] = LoadSound("assets/audio/sfx/sfx_explosion.wav");
        soundMap_[IMPACT_FLOOR] = LoadSound("assets/audio/sfx/sfx_impact_floor.wav");
        soundMap_[IMPACT_WATER] = LoadSound("assets/audio/sfx/sfx_impact_water.wav");
        soundMap_[NOTE] = LoadSound("assets/audio/sfx/sfx_lore.wav");
        soundMap_[PUSH] = LoadSound("assets/audio/sfx/sfx_push.wav");
        soundMap_[RESPAWN_ACTIVATE] = LoadSound("assets/audio/sfx/sfx_respawnpoint_activate.wav");
        soundMap_[RESPAWN_REACTIVATE] = LoadSound("assets/audio/sfx/sfx_respawnpoint_reactivate.wav");
        soundMap_[RUBBLE] = LoadSound("assets/audio/sfx/sfx_rubble_remove.wav");
        soundMap_[SHOT] = LoadSound("assets/audio/sfx/sfx_shot_pistol.wav");

        for (auto music : ambientMap_)
        {
            SetMusicVolume(music.second, CoreLogic::DataProcessing::DesignConfig::MUSIC_VOLUME);
        }
        for (auto sound : soundMap_)
        {
            SetSoundVolume(sound.second, CoreLogic::DataProcessing::DesignConfig::SFX_VOLUME);
        }

        playAmbient(AMBIENT_UNDERWORLD);
    }

    void SoundHandler::playSound(SoundEnum pa_sound)
    {
        std::lock_guard<std::mutex> lock(soundHandler_mutex_);
        if (pa_sound < soundMap_.size() && pa_sound != AMBIENT_UNDERWORLD && pa_sound != AMBIENT_OVERWORLD)
        {
            PlaySound(soundMap_[pa_sound]);
            return;
        }
        TraceLog(LOG_ERROR, "Invalid sound index %d", pa_sound);
    }

    void SoundHandler::update()
    {
        std::lock_guard<std::mutex> lock(soundHandler_mutex_);
        UpdateMusicStream(ambientMap_[currentAmbient_]);
        float timePlayed =
                GetMusicTimePlayed(ambientMap_[currentAmbient_]) / GetMusicTimeLength(ambientMap_[currentAmbient_]);
        if (timePlayed > 1.0f)
        {
            playAmbient(currentAmbient_);
        }
    }

    void SoundHandler::playAmbient(SoundHandler::SoundEnum pa_ambient)
    {
        std::lock_guard<std::mutex> lock(soundHandler_mutex_);
        if (pa_ambient < ambientMap_.size())
        {
            StopMusicStream(ambientMap_[currentAmbient_]);
            PlayMusicStream(ambientMap_[pa_ambient]);
            currentAmbient_ = pa_ambient;
        }
    }

    SoundHandler &SoundHandler::getInstance()
    {
        static SoundHandler instance;
        return instance;
    }
}