//
// Created by Josi on 03.09.2024.
//

#include "Vine.h"
#include "Store.h"

Vector2 CoreLogic::EventManagement::Object::Vine::getCoordinates() const
{
    return coordinates_;
}

int CoreLogic::EventManagement::Object::Vine::getNewElevation() const
{
    return newElevation;
}

CoreLogic::EventManagement::Object::Vine::Vine(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size,
        int pa_elevation, Vector2 pa_coordinates, int pa_newElevation, int pa_spriteState) :
        coordinates_(pa_coordinates), newElevation(pa_newElevation),
        Interaction(pa_position, pa_hitbox, pa_id, Actor::CollisionType::COLLISION, pa_size, true, pa_elevation, CLIMBING)
{
    if (CoreLogic::DataProcessing::ActorStorage::getCurrentLevelID() == 0){
        secondarySprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::VINE_UNTERWORLD_SECONDARY);
    } else {
        secondarySprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::VINE_OVERWORLD_SECONDARY);
    }

    if (elevation_ > newElevation)
    {
        primaryDirection_ = UserInterface::Direction::DOWN;
    } else
    {
        primaryDirection_ = UserInterface::Direction::UP;
    }

    initFrame(pa_spriteState);
}

void CoreLogic::EventManagement::Object::Vine::draw()
{
    if (glowing_)
    {
        Rectangle dest = {hitbox_.x + secondarySprite_.getRelativePosition().x, hitbox_.y + secondarySprite_.getRelativePosition().y,
                          secondarySprite_.getFrame().width, secondarySprite_.getFrame().height};

        DrawTexturePro(secondarySprite_.getTexture(), secondarySprite_.getFrame(), dest, {0, 0}, 0, WHITE);

    }
}

void CoreLogic::EventManagement::Object::Vine::setCoordinates(Vector2 pa_coordinates)
{
    coordinates_ = pa_coordinates;
}

void CoreLogic::EventManagement::Object::Vine::setNewElevation(int pa_newElevation)
{
    newElevation = pa_newElevation;
}




