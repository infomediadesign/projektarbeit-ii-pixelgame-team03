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

            Drone(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
                  CollisionType pa_collisionType, Vector2 pa_size, bool pa_visible,
                  int pa_elevation);


            void move(bool pa_up, bool pa_down, bool pa_left, bool pa_right);

            bool canInteract();
            bool canAct();


            void update();

        protected:
            void checkInteraction();

            virtual void setInteraction(int pa_actorID) = 0;
            virtual void setAbility(int pa_actorID) = 0;

            bool checkCollision(CoreLogic::UserInterface::Direction pa_direction, Vector2 pa_position);
            std::pair<int, int> interaction_;
            std::pair<int, int> action_;

        };
    }



#endif //RAYLIBSTARTER_PLAYER_H
