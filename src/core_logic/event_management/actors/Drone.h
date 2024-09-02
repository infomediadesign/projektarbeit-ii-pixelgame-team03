//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_PLAYER_H
#define RAYLIBSTARTER_PLAYER_H


#include <memory>
#include "MovableActor.h"
#include "objects/Ability.h"
#include "objects/Interaction.h"


namespace CoreLogic::EventManagement::Actors
    {
        class Drone : public MovableActor
        {
        public:
            enum DroneType
            {
                WORKER,
                SCOUT
            };

            Drone(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
                  CollisionType pa_collisionType, Vector2 pa_size, bool pa_visible,
                  int pa_elevation);


            void move(bool pa_up, bool pa_down, bool pa_left, bool pa_right);
            int getMaxHealth() const;
            int getCurrentHealth() const;
            DroneType getDroneType() const;

            void inceaseMaxHealth();
            void increaseCurrentHealth();
            void decreaseCurrentHealth();
            bool canInteract();
            bool canAct();

            std::shared_ptr<CoreLogic::EventManagement::Object::Interaction> getInteraction();
            std::shared_ptr<CoreLogic::EventManagement::Object::Ability> getAbility();


            virtual void update();

        protected:
            void checkInteraction();
            virtual void checkAbility() = 0;

            void setInteraction(std::shared_ptr<CoreLogic::EventManagement::Object::Interaction> pa_interaction);
            void setAbility(std::shared_ptr<CoreLogic::EventManagement::Object::Ability> pa_ability);

            bool checkCollision(CoreLogic::UserInterface::Direction pa_direction, Vector2 pa_position);
            /**
             * @Pseudo_Code: Interactions and Abilities not yet existing
             */
            std::shared_ptr<CoreLogic::EventManagement::Object::Interaction> interaction_;
            std::shared_ptr<CoreLogic::EventManagement::Object::Ability> ability_;

            int maxHealth = 3;
            int currentHealth = 3;
            DroneType currentDroneType = DroneType::WORKER;

        };
    }



#endif //RAYLIBSTARTER_PLAYER_H
