//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_PLAYER_H
#define RAYLIBSTARTER_PLAYER_H


#include "event_management/Actor.h"



    namespace CoreLogic::EventManagement::Actors
    {
        class Drone : public Actor
        {
        public:
            Drone() = delete;
            Drone(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size);
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
