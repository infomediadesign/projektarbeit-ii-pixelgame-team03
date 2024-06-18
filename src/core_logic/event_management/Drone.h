//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_PLAYER_H
#define RAYLIBSTARTER_PLAYER_H


#include "Actor.h"


namespace CoreLogic::EventManagement
{
    class Drone : public Actor
    {
    public:
        Drone() = delete;
        Drone(Vector2 pa_position, Rectangle pa_hitbox, int pa_id);
        void move(bool pa_up, bool pa_down, bool pa_left, bool pa_right);
    private:
        bool checkCollision();
    };
}


#endif //RAYLIBSTARTER_PLAYER_H
