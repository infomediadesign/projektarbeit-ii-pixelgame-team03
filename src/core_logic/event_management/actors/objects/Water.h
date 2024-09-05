//
// Created by Josi on 05.09.2024.
//

#ifndef HIVE_WATER_H
#define HIVE_WATER_H

#include "Actor.h"

namespace CoreLogic::EventManagement::Object
{
    class Water : public Actor
    {
        public:
        Water(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation);

    };
}

#endif //HIVE_WATER_H
