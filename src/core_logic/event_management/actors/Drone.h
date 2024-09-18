//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_PLAYER_H
#define RAYLIBSTARTER_PLAYER_H


#include <memory>
#include "MovableActor.h"
#include "objects/Ability.h"
#include "objects/Interaction.h"
#include "data_processing/DesignConfig.h"


namespace CoreLogic::EventManagement::Actors
    {
        class Drone : public MovableActor
        {
        public:
            enum DroneType
            {
                NONE = -1,
                WORKER = 0,
                SCOUT = 1
            };

            enum DroneState
            {
                MOVING,
                INTERACTING,
                ABILITY,
                DEATH,
                JUMP,
                DEATH_ABILITY
            };

            Drone(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation);
            Drone(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, int pa_maxHealth, int pa_currentHealth);


            void move(bool pa_up, bool pa_down, bool pa_left, bool pa_right);

            int getMaxHealth() const;
            void setMaxHealth(int pa_maxHealth);

            int getCurrentHealth() const;
            void setCurrentHealth(int pa_currentHealth);

            [[nodiscard]] DroneType getDroneType() const;
            void setDroneType(DroneType pa_droneType);

            std::shared_ptr<CoreLogic::EventManagement::Object::Interaction> getInteraction();
            void setInteraction(std::shared_ptr<CoreLogic::EventManagement::Object::Interaction> pa_interaction);

            std::shared_ptr<CoreLogic::EventManagement::Object::Ability> getAbility();
            void setAbility(std::shared_ptr<CoreLogic::EventManagement::Object::Ability> pa_ability);

            void increaseMaxHealth();
            void increaseCurrentHealth();
            void decreaseCurrentHealth();

            bool canInteract();
            bool canAct();
            bool isDying();
            bool canMove();
            bool canDeathAbility();

            virtual void update();

            void setDroneState(DroneState pa_droneState);
            [[nodiscard]] DroneState getDroneState() const;
            void removeDroneState(DroneState pa_droneState);

        protected:
            void checkInteraction();
            virtual void checkAbility() = 0;

            bool checkCollision(CoreLogic::UserInterface::Direction pa_direction, Vector2 pa_position);

            std::shared_ptr<CoreLogic::EventManagement::Object::Interaction> interaction_;
            std::shared_ptr<CoreLogic::EventManagement::Object::Ability> ability_;

            int maxHealth_ = CoreLogic::DataProcessing::DesignConfig::STARTING_MAX_DRONE_LIFE;
            int currentHealth_ = CoreLogic::DataProcessing::DesignConfig::STARTING_CURRENT_DRONE_LIFE;
            DroneType currentDroneType_ = DroneType::WORKER;
            DroneState currentDroneState_ = DroneState::MOVING;

            int speed_ = CoreLogic::DataProcessing::DesignConfig::DRONE_SPEED;
        };
    }



#endif //RAYLIBSTARTER_PLAYER_H
