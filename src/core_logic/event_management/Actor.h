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
        Actor(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size);
        virtual ~Actor() = default;
        int getId();
        Rectangle getHitbox();
        virtual void shiftFrame() = 0;

    protected:
        Vector2 position_;
        Rectangle hitbox_;
        const int id_;
        const Vector2 size_;

        /**
         *@todo: implement sprites
         **/
    };
}



#endif //RAYLIBSTARTER_ACTOR_H
