//
// Created by Josi on 03.09.2024.
//

#include "DroneRespawnPoint.h"

void CoreLogic::EventManagement::Object::DroneRespawnPoint::changeState(
        CoreLogic::EventManagement::Object::DroneRespawnPoint::DroneRespawnPointState pa_state)
{
    state_ = pa_state;
    shiftFrame(pa_state);
}

CoreLogic::EventManagement::Object::DroneRespawnPoint::DroneRespawnPointState
CoreLogic::EventManagement::Object::DroneRespawnPoint::getRespawnState() const
{
    return state_;
}
