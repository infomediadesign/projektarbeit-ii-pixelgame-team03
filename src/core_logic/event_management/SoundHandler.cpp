//
// Created by Josi on 08.08.2024.
//

#include <iostream>
#include "SoundHandler.h"

SoundHandler::SoundHandler()
{
    //todo: add bool currentlyPlaying
    soundMap.insert({0, std::vector<Sound>()});
    soundMap[0].push_back(LoadSound("assets/audio/tracks/hive_AUDI_sample-ambient.wav"));
}

void SoundHandler::playSound(int eventID)
{
    //todo: check if available
    //todo: check if playing
    //todo: how does playing multiple sounds in one event work? given by event?
    //todo: why not enums if there is a certain int for everything anyways? actually we have event_enum. that should work
    auto it = soundMap.at(eventID);
    PlaySound(it[0]);
    std::cout << "playing sound" << std::endl;
}
