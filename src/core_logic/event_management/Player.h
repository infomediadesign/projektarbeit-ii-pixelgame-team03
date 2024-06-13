//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_PLAYER_H
#define RAYLIBSTARTER_PLAYER_H


#include "Actor.h"


namespace CoreLogic::EventManagement
{
    class Player : public Actor
    {
    public:
        void move(bool pa_up, bool pa_down, bool pa_left, bool pa_right);
    private:
        void checkCollision();
    };
}


#endif //RAYLIBSTARTER_PLAYER_H
