//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_PLAYER_H
#define RAYLIBSTARTER_PLAYER_H


#include <memory>
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

            void inceaseMaxHealth();
            void increaseCurrentHealth();
            void decreaseCurrentHealth();
            bool canInteract();
            bool canAct();

            shared_ptr<Interaction> getInteraction();
            shared_ptr<Ability> getAbility();


            virtual void update();

        protected:
            void checkInteraction();
            virtual void checkAbility() = 0;

            void setInteraction(Interaction pa_interaction);
            void setAbility(Ability pa_ability);

            bool checkCollision(CoreLogic::UserInterface::Direction pa_direction, Vector2 pa_position);
            /**
             * @Pseudo_Code: Interactions and Abilities not yet existing
             */
            std::shared_ptr<Interaction> interaction_;
            std::shared_ptr<Ability> ability_;

            int maxHealth = 3;
            int currentHealth = 3;

        };
    }



#endif //RAYLIBSTARTER_PLAYER_H
