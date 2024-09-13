//
// Created by Josi on 03.09.2024.
//

#include "Vine.h"

Vector2 CoreLogic::EventManagement::Object::Vine::getCoordinates() const
{
    return coordinates_;
}

int CoreLogic::EventManagement::Object::Vine::getNewElevation() const
{
    return newElevation;
}

CoreLogic::EventManagement::Object::Vine::Vine(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size,
        int pa_elevation, Vector2 pa_coordinates, int pa_newElevation) :
        coordinates_(pa_coordinates), newElevation(pa_newElevation),
        Interaction(pa_position, pa_hitbox, pa_id, Actor::CollisionType::COLLISION, pa_size, false, pa_elevation, CLIMBING)
{

}

void CoreLogic::EventManagement::Object::Vine::setCoordinates(Vector2 pa_coordinates)
{
coordinates_ = pa_coordinates;
}

void CoreLogic::EventManagement::Object::Vine::setNewElevation(int pa_newElevation)
{
newElevation = pa_newElevation;
}




