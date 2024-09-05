//
// Created by Josi on 02.09.2024.
//

#include "Barrel.h"

namespace CoreLogic::EventManagement::Object
{
    int Barrel::getNewElevation() const
    {
        return newElevation_;
    }

    Barrel::Barrel(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation,
    int pa_fallHeight, UserInterface::Direction pa_primaryDirection) :
    primaryDirection_ (pa_primaryDirection),

    Ability(pa_position, pa_hitbox, pa_id, CollisionType::COLLISION, pa_size, true, pa_elevation, BARREL),
    Actors::MovableActor(pa_position, pa_hitbox, pa_id, CollisionType::COLLISION, pa_size, true, pa_elevation),
    Actor(pa_position, pa_hitbox, pa_id, CollisionType::COLLISION, pa_size, true, pa_elevation),
    Cliff(pa_position, pa_hitbox, pa_id, pa_size, pa_elevation, pa_fallHeight)
    {
        newElevation_ = pa_elevation - (pa_fallHeight / 2);
    }
}