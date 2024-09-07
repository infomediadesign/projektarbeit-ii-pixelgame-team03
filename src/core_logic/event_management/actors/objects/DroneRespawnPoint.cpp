//
// Created by Josi on 03.09.2024.
//

#include "DroneRespawnPoint.h"
#include "data_processing/Store.h"

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

CoreLogic::EventManagement::Object::DroneRespawnPoint::DroneRespawnPoint(Vector2 pa_position, Rectangle pa_hitbox,
        int pa_id, Vector2 pa_size, int pa_elevation) :
        Interaction(pa_position, pa_hitbox, pa_id, Actor::CollisionType::NONE, pa_size, true, pa_elevation,
                CHECKPOINT)
{
    sprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::SPAWN_UNDERWORLD);
}
