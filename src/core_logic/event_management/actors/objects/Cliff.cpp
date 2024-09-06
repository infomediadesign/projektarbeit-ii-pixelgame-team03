//
// Created by Josi on 03.09.2024.
//

#include "Cliff.h"


int CoreLogic::EventManagement::Object::Cliff::getFallHeight() const
{
    return fallHeight_;
}

CoreLogic::EventManagement::Object::Cliff::Cliff(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size,
        int pa_elevation, int pa_fallHeight) : fallHeight_(pa_fallHeight + 1), Actor(pa_position, pa_hitbox, pa_id, Actor::CollisionType::COLLISION, pa_size, false, pa_elevation)
{

}

void CoreLogic::EventManagement::Object::Cliff::setFallHeight(int pa_fallHeight)
{
fallHeight_ = pa_fallHeight;
}
