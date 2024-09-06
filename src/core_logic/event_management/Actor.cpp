//
// Created by keanu on 5/23/2024.
//

#include "Actor.h"



int CoreLogic::EventManagement::Actor::getElevation() const
{
    return elevation_;
}

void CoreLogic::EventManagement::Actor::setElevation(int pa_elevation)
{
    elevation_ = pa_elevation;
}

void CoreLogic::EventManagement::Actor::shiftFrame(int pa_stateID)
{
    sprite_.shiftFrame(pa_stateID, primaryDirection_);
}

void CoreLogic::EventManagement::Actor::resetFrame(int pa_stateID)
{
    sprite_.resetFrame(pa_stateID);
}

Vector2 CoreLogic::EventManagement::Actor::getPosition() const
{
    return position_;
}

void CoreLogic::EventManagement::Actor::setPosition(Vector2 pa_position)
{
    position_ = pa_position;
}

Rectangle CoreLogic::EventManagement::Actor::getHitbox() const
{
    return hitbox_;
}

void CoreLogic::EventManagement::Actor::setHitbox(Rectangle pa_hitbox)
{
hitbox_ = pa_hitbox;
}

int CoreLogic::EventManagement::Actor::getId() const
{
    return id_;
}

CoreLogic::EventManagement::Actor::CollisionType CoreLogic::EventManagement::Actor::getCollisionType() const
{
    return collisionType_;
}

void
CoreLogic::EventManagement::Actor::setCollisionType(CoreLogic::EventManagement::Actor::CollisionType pa_collisionType)
{
collisionType_ = pa_collisionType;
}

bool CoreLogic::EventManagement::Actor::getVisible() const
{
    return visible_;
}

void CoreLogic::EventManagement::Actor::setVisible(bool pa_visible)
{
visible_ = pa_visible;
}

Vector2 CoreLogic::EventManagement::Actor::getSize() const
{
    return size_;
}

CoreLogic::UserInterface::Sprite CoreLogic::EventManagement::Actor::getSprite()
{
    return sprite_;
}

void CoreLogic::EventManagement::Actor::setSprite(CoreLogic::UserInterface::Sprite pa_sprite)
{
sprite_ = pa_sprite;
}

CoreLogic::UserInterface::Direction CoreLogic::EventManagement::Actor::getPrimaryDirection()
{
    return primaryDirection_;
}

void CoreLogic::EventManagement::Actor::setPrimaryDirection(CoreLogic::UserInterface::Direction pa_primaryDirection)
{
primaryDirection_ = pa_primaryDirection;
}

void CoreLogic::EventManagement::Actor::draw()
{
    Rectangle dest = {hitbox_.x + sprite_.getRelativePosition().x, hitbox_.y + sprite_.getRelativePosition().y,
            sprite_.getFrame().width, sprite_.getFrame().height};

}




