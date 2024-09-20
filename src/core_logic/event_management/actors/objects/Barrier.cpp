//
// Created by Josi on 03.09.2024.
//

#include "Barrier.h"

CoreLogic::EventManagement::Object::Barrier::Barrier(Vector2 pa_position,
        Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation) :
        Actor(pa_position,pa_hitbox,pa_id,CollisionType::COLLISION,pa_size,false,pa_elevation)
{

}
