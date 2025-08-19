//
// Created by Josi on 19.09.2024.
//

#include "CameraPan.h"

CoreLogic::EventManagement::Object::CameraPan::CameraPan(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
        Vector2 pa_size, int pa_elevation, Vector2 pa_destination, int pa_panTicks, int pa_restingTicks)
        : destination_(pa_destination), panTicks_(pa_panTicks), restingTicks_(pa_restingTicks), Actor(pa_position, pa_hitbox, pa_id, Actor::CollisionType::WALKABLE, pa_size, false, pa_elevation)
{

}

Vector2 CoreLogic::EventManagement::Object::CameraPan::getDestination() const
{
    return destination_;
}

void CoreLogic::EventManagement::Object::CameraPan::setDestination(Vector2 pa_destination)
{
 destination_ = pa_destination;
}

bool CoreLogic::EventManagement::Object::CameraPan::getPlayed() const
{
    return played_;
}

void CoreLogic::EventManagement::Object::CameraPan::setPlayed(bool pa_played)
{
    played_ = pa_played;
}

int CoreLogic::EventManagement::Object::CameraPan::getPanTicks() const
{
    return panTicks_;
}

void CoreLogic::EventManagement::Object::CameraPan::setPanTicks(int pa_panTicks)
{
panTicks_ = pa_panTicks;
}

int CoreLogic::EventManagement::Object::CameraPan::getRestingTicks() const
{
    return restingTicks_;
}

void CoreLogic::EventManagement::Object::CameraPan::setRestingTicks(int pa_restingTicks)
{
restingTicks_ = pa_restingTicks;
}
