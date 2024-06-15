//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_ACTOR_H
#define RAYLIBSTARTER_ACTOR_H


#include <raylib.h>

namespace CoreLogic::EventManagement
{
    class Actor
    {
    public:
        Actor(Vector2 pa_position, Rectangle pa_hitbox, int pa_id);
        ~Actor();

    protected:
        Vector2 position_;
        Rectangle hitbox_;
        int id_;
    };
}



#endif //RAYLIBSTARTER_ACTOR_H
