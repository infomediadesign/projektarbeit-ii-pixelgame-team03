//
// Created by keanu on 5/23/2024.
//

#include "Actor.h"

CoreLogic::EventManagement::Actor::Actor(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size): id_(pa_id),
                                                                                                                size_(pa_size)
{
    position_ = pa_position;
    hitbox_ = pa_hitbox;
}

int CoreLogic::EventManagement::Actor::getId()
{
    return id_;
}

Rectangle CoreLogic::EventManagement::Actor::getHitbox()
{
    return hitbox_;
}
