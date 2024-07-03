//
// Created by Josi on 12.06.2024.
//

#ifndef HIVE_MOVABLEACTOR_H
#define HIVE_MOVABLEACTOR_H

#include "../Actor.h"

namespace CoreLogic::EventManagement::Actors {

        class MovableActor : public Actor{
        public:
            MovableActor(Vector2& pa_position, Rectangle& pa_hitbox, int& pa_id, CollisionType& pa_collidable, Vector2& pa_size, bool& pa_visible, int& pa_elevation)
            : Actor(pa_position,pa_hitbox, pa_id, pa_collidable, pa_size, pa_visible, pa_elevation) {}
            virtual void move(bool pa_up, bool pa_down, bool pa_left, bool pa_right) = 0;
            void update();
            void draw();
        };

}
#endif //HIVE_MOVABLEACTOR_H
