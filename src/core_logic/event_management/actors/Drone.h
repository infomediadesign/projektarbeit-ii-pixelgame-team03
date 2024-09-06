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
            void setMaxHealth(int pa_maxHealth);

            int getCurrentHealth() const;
            void setCurrentHealth(int pa_currentHealth);

            DroneType getDroneType() const;
            void setDroneType(DroneType pa_droneType);

            std::shared_ptr<CoreLogic::EventManagement::Object::Interaction> getInteraction();
            void setInteraction(std::shared_ptr<CoreLogic::EventManagement::Object::Interaction> pa_interaction);

            std::shared_ptr<CoreLogic::EventManagement::Object::Ability> getAbility();
            void setAbility(std::shared_ptr<CoreLogic::EventManagement::Object::Ability> pa_ability);

            void inceaseMaxHealth();
            void increaseCurrentHealth();
            void decreaseCurrentHealth();
            bool canInteract();
            bool canAct();

            virtual void update();

        protected:
            void checkInteraction();
            virtual void checkAbility() = 0;

            bool checkCollision(CoreLogic::UserInterface::Direction pa_direction, Vector2 pa_position);

            std::shared_ptr<CoreLogic::EventManagement::Object::Interaction> interaction_;
            std::shared_ptr<CoreLogic::EventManagement::Object::Ability> ability_;

            int maxHealth_ = 3;
            int currentHealth_ = 3;
            DroneType currentDroneType_ = DroneType::WORKER;

        };
    }



#endif //RAYLIBSTARTER_PLAYER_H
