//
// Created by Josi on 02.09.2024.
//

#include "Ability.h"


CoreLogic::EventManagement::Object::Ability::AbilityType
CoreLogic::EventManagement::Object::Ability::getAbilityType() const
{
    return abilityType_;
}

CoreLogic::EventManagement::Object::Ability::Ability(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
        Actor::CollisionType pa_collisionType, Vector2 pa_size, bool pa_visible,
        int pa_elevation, AbilityType pa_abilityType) : abilityType_(pa_abilityType), Actors::MovableActor(pa_position, pa_hitbox, pa_id, pa_collisionType, pa_size, pa_visible, pa_elevation)
{

}

void CoreLogic::EventManagement::Object::Ability::setAbilityType(
        CoreLogic::EventManagement::Object::Ability::AbilityType pa_abilityType)
{
abilityType_ = pa_abilityType;
}

void CoreLogic::EventManagement::Object::Ability::setGlowing()
{
    glowing_ = true;
    sprite_.shiftFrame(/**@todo: Get glowing standart State*/);
}

void CoreLogic::EventManagement::Object::Ability::resetGlowing()
{
    glowing_ = false;
    if (sprite_.getCurrentStateId() == /**@todo Get glowing standart State*/)
    {
        sprite_.shiftFrame(/**@todo: Get standart idle State*/);
    }
}
