//
// Created by Josi on 03.09.2024.
//

#include "JumpPoint.h"

Vector2 CoreLogic::EventManagement::Object::JumpPoint::getJumpPosition() const
{
    return coordinates_;
}

CoreLogic::EventManagement::Object::JumpPoint::JumpPoint(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
        Vector2 pa_size, int pa_elevation, Vector2 pa_destination) :
        coordinates_(pa_destination),
        Ability(pa_position, pa_hitbox, pa_id, CollisionType::WALKABLE, pa_size, false, pa_elevation, JUMP)
{

}

void CoreLogic::EventManagement::Object::JumpPoint::setJumpPosition(Vector2 pa_position)
{
coordinates_ = pa_position;
}

