//
// Created by keanu on 5/23/2024.
//

#include "Actor.h"


CoreLogic::EventManagement::Actor::Actor(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, CollisionType pa_collidable, std::string pa_name, Vector2 pa_size, bool pa_visible, int pa_elevation) :
    position_(pa_position),
    hitbox_(pa_hitbox),
    id_(pa_id),
    collidable_(pa_collidable),
    visible_(pa_visible),
    name_(pa_name),
    size_(pa_size),
    elevation_(pa_elevation)
{
}

int CoreLogic::EventManagement::Actor::getElevation() const
{
    return elevation_;
}

void CoreLogic::EventManagement::Actor::setElevation(int pa_elevation)
{
    elevation_ = pa_elevation;
}

