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
        Ability(pa_position, pa_hitbox, pa_id, CollisionType::WALKABLE, pa_size, false, pa_elevation, JUMP),
        Actors::MovableActor(pa_position, pa_hitbox, pa_id, CollisionType::WALKABLE, pa_size,false, pa_elevation),
        Actor(pa_position, pa_hitbox, pa_id, CollisionType::WALKABLE, pa_size, false, pa_elevation)
{
//@todo: there HAS to be a way to chain constuctors so that this shit doesn't have 3 fucking initialiser lists
}

void CoreLogic::EventManagement::Object::JumpPoint::move(bool pa_up, bool pa_down, bool pa_left, bool pa_right)
{

}
