//
// Created by Josi on 02.09.2024.
//

#include "Rubble.h"

CoreLogic::EventManagement::Object::Rubble::Rubble(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation) :
        Ability(pa_position, pa_hitbox, pa_id, CollisionType::COLLISION, pa_size, true, pa_elevation, CLEANING)
{

}

void CoreLogic::EventManagement::Object::Rubble::setCleaned()
{
    this -> collisionType_ = Actor::CollisionType::NONE;
    this -> visible_ = false;
}
