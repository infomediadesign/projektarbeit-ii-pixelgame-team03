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

            Drone(Vector2 pa_position = {0, 0}, Rectangle pa_hitbox = {0, 0, 0, 0}, int pa_id = 0, CollisionType
            pa_collisionType = CollisionType::NONE, Vector2
                  pa_size = {32, 32}, bool pa_visible = true, int pa_elevation = 1)
                  : MovableActor(pa_position, pa_hitbox, pa_id, pa_collisionType, pa_size, pa_visible, pa_elevation)
            {};


            void move(bool pa_up, bool pa_down, bool pa_left, bool pa_right);


        private:

            bool checkCollision(Direction pa_direction, Vector2 pa_position);

        };
    }



#endif //RAYLIBSTARTER_PLAYER_H
