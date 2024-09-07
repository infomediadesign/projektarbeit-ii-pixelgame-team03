//
// Created by Josi on 02.09.2024.
//

#include "Barrel.h"
#include "data_processing/Store.h"

namespace CoreLogic::EventManagement::Object
{
    int Barrel::getNewElevation() const
    {
        return newElevation_;
    }

    Barrel::Barrel(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation,
    int pa_fallHeight, UserInterface::Direction pa_primaryDirection) :
    primaryDirection_ (pa_primaryDirection),
    Ability(pa_position, pa_hitbox, pa_id, CollisionType::COLLISION, pa_size, true, pa_elevation, BARREL)
    {
        newElevation_ = pa_elevation - (pa_fallHeight / 2);
        sprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::BARREL);
    }

    void Barrel::setNewElevation(int pa_newElevation)
    {
newElevation_ = pa_newElevation;
    }

    int Barrel::getFallHeight() const
    {
        return fallHeight_;
    }

    void Barrel::setFallHeight(int pa_fallHeight)
    {
fallHeight_ = pa_fallHeight;
    }
}