//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_BARRIER_H
#define HIVE_BARRIER_H

#include "event_management/Actor.h"

namespace CoreLogic::EventManagement::Object
{
    class Barrier : public Actor
    {
    public:
        Barrier(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size,
                bool pa_visible, int pa_elevation);
    };
}

#endif //HIVE_BARRIER_H
