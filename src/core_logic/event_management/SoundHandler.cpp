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
        ambientMap_[AMBIENT_OVERWORLD] = {LoadMusicStream("assets/audio/tracks/oberwelt_amb.wav"), CoreLogic::DataProcessing::DesignConfig::MUSIC_OVERWORLD_VOLUME};
        ambientMap_[AMBIENT_UNDERWORLD] = {LoadMusicStream("assets/audio/tracks/unterwelt_amb.wav"), CoreLogic::DataProcessing::DesignConfig::MUSIC_UNDERWORLD_VOLUME};

        soundMap_[EXPLOSION] = {LoadSound("assets/audio/sfx/sfx_explosion.wav"), CoreLogic::DataProcessing::DesignConfig::SFX_EXPLOSION_VOLUME};
        soundMap_[IMPACT_FLOOR] = {LoadSound("assets/audio/sfx/sfx_impact_floor.wav"), CoreLogic::DataProcessing::DesignConfig::SFX_IMPACT_FLOOR_VOLUME};
        soundMap_[IMPACT_WATER] = {LoadSound("assets/audio/sfx/sfx_impact_water.wav"), CoreLogic::DataProcessing::DesignConfig::SFX_IMPACT_WATER_VOLUME};
        soundMap_[NOTE] = {LoadSound("assets/audio/sfx/sfx_lore.wav"), CoreLogic::DataProcessing::DesignConfig::SFX_NOTE_VOLUME};
        soundMap_[PUSH] = {LoadSound("assets/audio/sfx/sfx_push.wav"), CoreLogic::DataProcessing::DesignConfig::SFX_PUSH_VOLUME};
        soundMap_[RESPAWN_ACTIVATE] = {LoadSound("assets/audio/sfx/sfx_respawnpoint_activate.wav"), CoreLogic::DataProcessing::DesignConfig::SFX_RESPAWN_ACTIVATE_VOLUME};
        soundMap_[RESPAWN_REACTIVATE] = {LoadSound("assets/audio/sfx/sfx_respawnpoint_reactivate.wav"), CoreLogic::DataProcessing::DesignConfig::SFX_RESPAWN_REACTIVATE_VOLUME};
        soundMap_[RUBBLE] = {LoadSound("assets/audio/sfx/sfx_rubble_remove.wav"), CoreLogic::DataProcessing::DesignConfig::SFX_RUBBLE_VOLUME};
        soundMap_[SHOT] = {LoadSound("assets/audio/sfx/sfx_shot_pistol.wav"), CoreLogic::DataProcessing::DesignConfig::SFX_SHOT_VOLUME};
        soundMap_[BELL] = {LoadSound("assets/audio/sfx/sfx_bell.wav"), CoreLogic::DataProcessing::DesignConfig::SFX_BELL_VOLUME};
        soundMap_[DEATH_DRONE] = {LoadSound("assets/audio/sfx/sfx_death_drone.wav"), CoreLogic::DataProcessing::DesignConfig::SFX_DEATH_DRONE_VOLUME};
        soundMap_[DEATH_HUMAN] = {LoadSound("assets/audio/sfx/sfx_death_human.wav"), CoreLogic::DataProcessing::DesignConfig::SFX_DEATH_HUMAN_VOLUME};

        for (auto music : ambientMap_)
        {
            SetMusicVolume(music.second.first, music.second.second);
        }
        for (auto sound : soundMap_)
        {
            SetSoundVolume(sound.second.first, sound.second.second);
        }

        playAmbient(AMBIENT_UNDERWORLD);
    }

    void SoundHandler::playSound(SoundEnum pa_sound)
    {
        std::lock_guard<std::mutex> lock(soundHandler_mutex_);
        if (pa_sound < soundMap_.size() && pa_sound != AMBIENT_UNDERWORLD && pa_sound != AMBIENT_OVERWORLD)
        {
            PlaySound(soundMap_[pa_sound].first);
            return;
        }
        TraceLog(LOG_ERROR, "Invalid sound index %d", pa_sound);
    }

    void SoundHandler::update()
    {
        std::lock_guard<std::mutex> lock(soundHandler_mutex_);
        UpdateMusicStream(ambientMap_[currentAmbient_].first);
        float timePlayed =
                GetMusicTimePlayed(ambientMap_[currentAmbient_].first) / GetMusicTimeLength(ambientMap_[currentAmbient_].first);
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
            StopMusicStream(ambientMap_[currentAmbient_].first);
            PlayMusicStream(ambientMap_[pa_ambient].first);
            currentAmbient_ = pa_ambient;
            return;
        }
    }

    SoundHandler &SoundHandler::getInstance()
    {
        static SoundHandler instance;
        return instance;
    }
}