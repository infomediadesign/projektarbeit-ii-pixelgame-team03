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
        int pa_id, Vector2 pa_size, int pa_elevation, bool pa_newDrone, int pa_unlockType, bool pa_active, int
        pa_level) :
        newDrone_(pa_newDrone), unlockType_(pa_unlockType),
        Interaction(pa_position, pa_hitbox, pa_id, Actor::CollisionType::NONE, pa_size, true, pa_elevation,
                CHECKPOINT)
{
    if (CoreLogic::DataProcessing::ActorStorage::getCurrentLevelID() == 0){
        sprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::SPAWN_UNDERWORLD);
    } else {
        sprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::SPAWN_OVERWORLD);
    }
    secondarySprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::SPAWN_SECONDARY);

    level_ = pa_level;

    unlockType_ = (CoreLogic::EventManagement::Actors::Drone::DroneType) pa_unlockType;

    if (pa_active == true)
    {
        changeState(DroneRespawnPointState::ACTIVATED);
    } else {
        changeState(DroneRespawnPointState::UNDISCOVERED);
        if (pa_newDrone == true)
        {
            shiftFrame(3);
        }
    }
}

bool CoreLogic::EventManagement::Object::DroneRespawnPoint::getNewDrone() const
{
    return newDrone_;
}

void CoreLogic::EventManagement::Object::DroneRespawnPoint::setNewDrone(bool pa_newDrone)
{
    newDrone_ = pa_newDrone;
}

int CoreLogic::EventManagement::Object::DroneRespawnPoint::getUnlockType() const
{
    return unlockType_;
}

void CoreLogic::EventManagement::Object::DroneRespawnPoint::setUnlockType(int pa_unlockType)
{
    unlockType_ = pa_unlockType;
}

int CoreLogic::EventManagement::Object::DroneRespawnPoint::getLevel() const
{
    return level_;
}

void CoreLogic::EventManagement::Object::DroneRespawnPoint::setLevel(int pa_level)
{
    level_ = pa_level;
}

void CoreLogic::EventManagement::Object::DroneRespawnPoint::setGlowing()
{
    Interaction::setGlowing();
    if (newDrone_ && state_ == DroneRespawnPointState::UNDISCOVERED)
    {
        secondarySprite_.shiftFrame(1);
    } else {
        secondarySprite_.shiftFrame(0);
    }
}
