//
// Created by Josi on 03.09.2024.
//

#include "LevelSwitch.h"

int CoreLogic::EventManagement::Object::LevelSwitch::getNewLevelID() const
{
    return newLevelID_;
}

CoreLogic::EventManagement::Object::LevelSwitch::LevelSwitch(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
        Vector2 pa_size, int pa_elevation, int pa_newLevelID) :
        newLevelID_(pa_newLevelID),
        Actor(pa_position, pa_hitbox, pa_id, Actor::CollisionType::WALKABLE, pa_size, false, pa_elevation)
{

}
