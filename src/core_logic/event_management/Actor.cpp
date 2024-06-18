//
// Created by keanu on 5/23/2024.
//

#include "Actor.h"

CoreLogic::EventManagement::Actor::Actor(Vector2 pa_position, Rectangle pa_hitbox, int pa_id)
{
    position_ = pa_position;
    hitbox_ = pa_hitbox;
    id_ = pa_id;
}

int CoreLogic::EventManagement::Actor::getId()
{
    return id_;
}
