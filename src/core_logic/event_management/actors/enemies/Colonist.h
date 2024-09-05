//
// Created by Josi on 15.06.2024.
//

#ifndef HIVE_COLONIST_H
#define HIVE_COLONIST_H

#include "../../Actor.h"

namespace CoreLogic::EventManagement::Actors {

            class Colonist : public EventManagement::Actor{

            public:
                Colonist(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation)
                : Actor(pa_position, pa_hitbox, pa_id, pa_collidable, pa_size, true, pa_elevation) {};

            };

}

#endif //HIVE_COLONIST_H
