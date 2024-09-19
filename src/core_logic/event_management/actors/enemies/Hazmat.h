//
// Created by Josi on 15.06.2024.
//

#ifndef HIVE_HAZMAT_H
#define HIVE_HAZMAT_H

#include "event_management/Actor.h"

namespace CoreLogic::EventManagement::Actors {

            class Hazmat : public EventManagement::Actor{

            public:
                Hazmat(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, CollisionType pa_collidable, Vector2 pa_size, bool pa_visible, int pa_elevation)
                : Actor(pa_position, pa_hitbox, pa_id, pa_collidable, pa_size, pa_visible, pa_elevation) {};

            };

}

#endif //HIVE_HAZMAT_H
