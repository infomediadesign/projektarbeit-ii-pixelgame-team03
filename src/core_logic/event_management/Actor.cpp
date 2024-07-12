//
// Created by keanu on 5/23/2024.
//

#include "Actor.h"



int CoreLogic::EventManagement::Actor::getElevation() const
{
    return elevation_;
}

void CoreLogic::EventManagement::Actor::setElevation(int pa_elevation)
{
    elevation_ = pa_elevation;
}

void CoreLogic::EventManagement::Actor::shiftFrame(int pa_stateID)
{
    sprite_.shiftFrame(pa_stateID, primaryDirection_);
}

void CoreLogic::EventManagement::Actor::resetFrame(int pa_stateID)
{
    sprite_.resetFrame(pa_stateID);
}

