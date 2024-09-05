//
// Created by Josi on 02.09.2024.
//

#ifndef HIVE_BARREL_H
#define HIVE_BARREL_H

#include "Ability.h"
#include "Cliff.h"

namespace CoreLogic::EventManagement::Object
{
class Barrel : public Ability
    {
    public:
        Barrel(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, int pa_fallHeight, UserInterface::Direction pa_primaryDirection);

        int getNewElevation() const;
        int getFallHeight() const;

    protected:
        int newElevation_ = 0;
        int fallHeight_ = 0;
        UserInterface::Direction primaryDirection_ = UserInterface::Direction::UP;
    };
}

#endif //HIVE_BARREL_H
