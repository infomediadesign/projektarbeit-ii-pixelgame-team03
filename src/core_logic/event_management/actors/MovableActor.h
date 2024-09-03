//
// Created by Josi on 12.06.2024.
//

#ifndef HIVE_MOVABLEACTOR_H
#define HIVE_MOVABLEACTOR_H

#include "../Actor.h"

namespace CoreLogic::EventManagement::Actors
{

    class MovableActor : virtual public Actor
    {
    public:
        enum State
        {
            IDLE,
            WALKING,
            MAIN_ABILITY,
            DEATH_ABILITY,
            DEATH,
            CLIMBING,
            FALLING,
        };

        MovableActor(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, CollisionType pa_collisionType, Vector2
        pa_size, bool pa_visible, int pa_elevation)
                : Actor(pa_position, pa_hitbox, pa_id, pa_collisionType, pa_size, pa_visible, pa_elevation)
        {}

        virtual void move(bool pa_up, bool pa_down, bool pa_left, bool pa_right) = 0;

        void setPosition(Vector2 pa_position);


    protected:
        void updateHitbox();

        /**
         * @Outdated
         */
        void adjustOutOfBounds();
    };

}
#endif //HIVE_MOVABLEACTOR_H
