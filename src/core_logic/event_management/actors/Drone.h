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
            int getMaxHealth();
            int getCurrentHealth();
            int getInteract();
            int getDroneType();

            void inceaseMaxHealth();
            void increaseCurrentHealth();
            void decreaseCurrentHealth();

            void toggleInteract();
            void toggleDroneType();


        private:

            bool checkCollision(CoreLogic::UserInterface::Direction pa_direction, Vector2 pa_position);
            int maxHealth = 3;
            int currentHealth = 3;

            bool canInteract = false;
            int droneType = 0;

        };
    }



#endif //RAYLIBSTARTER_PLAYER_H
