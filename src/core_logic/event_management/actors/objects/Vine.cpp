//
// Created by Josi on 03.09.2024.
//

#include "Vine.h"

Vector2 CoreLogic::EventManagement::Object::Vine::getCoordinates() const
{
    return coordinates_;
}

int CoreLogic::EventManagement::Object::Vine::getElevationChange() const
{
    return elevationChange_;
}

CoreLogic::EventManagement::Object::Vine::Vine(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size,
        int pa_elevation, Vector2 pa_coordinates) :
        coordinates_(pa_coordinates),
        Interaction(pa_position, pa_hitbox, pa_id, Actor::CollisionType::COLLISION, pa_size, false, pa_elevation, CLIMBING)
{
    elevationChange_ = (int) ((pa_coordinates.y - pa_position.y) / 24) / 2;
}




