//
// Created by Josi on 05.09.2024.
//

#include "Water.h"

CoreLogic::EventManagement::Object::Water::Water(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size,
        int pa_elevation) :
        Actor(pa_position, pa_hitbox, pa_id, CollisionType::ENEMYDEATH, pa_size, true, pa_elevation)
{

}
