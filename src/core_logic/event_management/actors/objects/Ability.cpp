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
