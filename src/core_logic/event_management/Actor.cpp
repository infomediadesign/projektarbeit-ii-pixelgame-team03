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

void CoreLogic::EventManagement::Actor::shiftFrame(int pa_stateID, Direction pa_primaryDirection)
{
    sprite_.shiftFrame(pa_stateID, pa_primaryDirection);
}

