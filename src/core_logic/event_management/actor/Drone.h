//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_PLAYER_H
#define RAYLIBSTARTER_PLAYER_H


#include "MovableActor.h"


    namespace CoreLogic::EventManagement::Actors
    {
        class Drone : public MovableActor
        {
        public:
            Drone() = delete;
            Drone(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, CollisionType pa_collisionType, Vector2 pa_size, bool pa_visible, int pa_elevation)
            : MovableActor( pa_position, pa_hitbox, pa_id, pa_collisionType, pa_size, pa_visible, pa_elevation) {};
            void move(bool pa_up, bool pa_down, bool pa_left, bool pa_right);

            Vector2 getPosition();

        private:
            enum class Direction {
                UP,
                DOWN,
                LEFT,
                RIGHT
            };
            bool checkCollision(Direction pa_direction, Vector2 pa_position);
        };
    }



#endif //RAYLIBSTARTER_PLAYER_H
