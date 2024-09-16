//
// Created by Josi on 03.09.2024.
//

#include "LevelSwitch.h"

int CoreLogic::EventManagement::Object::LevelSwitch::getNewLevelID() const
{
    return newLevelID_;
}

CoreLogic::EventManagement::Object::LevelSwitch::LevelSwitch(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
        Vector2 pa_size, int pa_elevation, int pa_newLevelID, Vector2 pa_switchCoordinates, int pa_switchElevation) :
        newLevelID_(pa_newLevelID), switchElevation_(pa_switchElevation), switchCoordinates_(pa_switchCoordinates),
        Actor(pa_position, pa_hitbox, pa_id, Actor::CollisionType::WALKABLE, pa_size, false, pa_elevation)
{

}

void CoreLogic::EventManagement::Object::LevelSwitch::setNewLevelID(int pa_newLevelID)
{
newLevelID_ = pa_newLevelID;
}

Vector2 CoreLogic::EventManagement::Object::LevelSwitch::getSwitchCoordinates() const
{
    return switchCoordinates_;
}

void CoreLogic::EventManagement::Object::LevelSwitch::setSwitchCoordinates(Vector2 pa_switchCoordinates)
{
    switchCoordinates_ = pa_switchCoordinates;
}

int CoreLogic::EventManagement::Object::LevelSwitch::getSwitchElevation() const
{
    return switchElevation_;
}

void CoreLogic::EventManagement::Object::LevelSwitch::setSwitchElevation(int pa_switchElevation)
{
    switchElevation_ = pa_switchElevation;
}
