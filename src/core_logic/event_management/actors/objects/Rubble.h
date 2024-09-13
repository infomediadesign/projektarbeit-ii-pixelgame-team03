//
// Created by Josi on 02.09.2024.
//

#ifndef HIVE_RUBBLE_H
#define HIVE_RUBBLE_H

#include "Ability.h"

namespace CoreLogic::EventManagement::Object
{
    class Rubble : public Ability
    {
        public:
        Rubble(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2
        pa_size, int pa_elevation);
        void setCleaned();
    };
}

#endif //HIVE_RUBBLE_H
