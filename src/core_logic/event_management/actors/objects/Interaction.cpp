//
// Created by Josi on 02.09.2024.
//

#include "Interaction.h"

CoreLogic::EventManagement::Object::Interaction::InteractionType
CoreLogic::EventManagement::Object::Interaction::getType() const
{
    return type_;
}

CoreLogic::EventManagement::Object::Interaction::Interaction(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
        Actor::CollisionType pa_collidable, Vector2 pa_size, bool pa_visible,
        int pa_elevation, InteractionType pa_type) :
        type_(pa_type),

        Actor(pa_position, pa_hitbox, pa_id, pa_collidable, pa_size, pa_visible, pa_elevation)
{

}

void CoreLogic::EventManagement::Object::Interaction::setType(
        CoreLogic::EventManagement::Object::Interaction::InteractionType pa_type)
{
type_ = pa_type;
}
