//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_CLIFF_H
#define HIVE_CLIFF_H

#include "Actor.h"

namespace CoreLogic::EventManagement::Object
{
    class Cliff : virtual public Actor
    {
    public:
        Cliff(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, int pa_fallHeight);
        int getFallHeight() const;
    protected:
        int fallHeight_ = 0;
    };
}

#endif //HIVE_CLIFF_H
