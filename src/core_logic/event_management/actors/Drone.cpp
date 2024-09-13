//
// Created by keanu on 5/23/2024.
//

#include "Drone.h"
#include "raylib.h"
#include "../../../tileson.h"
#include "event_management/EventHandler.h"
#include "data_processing/TilesonUtilities.h"
#include "data_processing/Store.h"
#include "Sprite.h"
#include "data_processing/DesignConfig.h"

namespace CoreLogic::EventManagement::Actors
{

    void Drone::move(bool pa_up, bool pa_down, bool pa_left, bool pa_right)
    {

        EventHandler &eventHandler = EventHandler::getInstance();

        int tickMult = CoreLogic::DataProcessing::global_ticks % 3;
        int diagonalSpeed;
        if (speed_ == 1)
        {
            diagonalSpeed = (1 - ((int) (tickMult / 2)));
        } else
        {
            diagonalSpeed = ((speed_ / 2) +
                             (speed_ % 2) + ((int) (tickMult / 2)));
        }
        if (pa_up && !pa_down)
        {
            (pa_right || pa_left) ? position_.y -= diagonalSpeed
                                  : position_.y -= speed_;
            updateHitbox();
            if (checkCollision(CoreLogic::UserInterface::Direction::UP, position_))
            {
                eventHandler.handleEvents({DISCONNECT}, id_);
            }
        }

        if (pa_down && !pa_up)
        {
            (pa_right || pa_left) ? position_.y += diagonalSpeed
                                  : position_.y += speed_;
            updateHitbox();
            if (checkCollision(CoreLogic::UserInterface::Direction::DOWN, {position_.x, position_.y + size_.y}))
            {
                eventHandler.handleEvents({DISCONNECT}, id_);
            }
        }

        if (pa_left && !pa_right)
        {
            (pa_up || pa_down) ? position_.x -= diagonalSpeed
                               : position_.x -= speed_;
            updateHitbox();
            if (checkCollision(CoreLogic::UserInterface::Direction::LEFT, position_))
            {
                eventHandler.handleEvents({DISCONNECT}, id_);
            }
        }

        if (pa_right && !pa_left)
        {
            (pa_up || pa_down) ? position_.x += diagonalSpeed
                               : position_.x += speed_;
            updateHitbox();
            if (checkCollision(CoreLogic::UserInterface::Direction::RIGHT, {position_.x + size_.x, position_.y}))
            {
                eventHandler.handleEvents({DISCONNECT}, id_);
            }
        }
    }

    bool Drone::checkCollision(CoreLogic::UserInterface::Direction pa_direction, Vector2 pa_position)
    {

        std::vector<std::shared_ptr<Actor>> actors = CoreLogic::DataProcessing::ActorStorage::getCollidables()->at(elevation_);
        std::vector<std::shared_ptr<Object::Cliff>> cliffs = CoreLogic::DataProcessing::ActorStorage::getCliffs()->at(elevation_);
        actors.insert(actors.end(), cliffs.begin(), cliffs.end());

//        std::map<int, std::vector<std::shared_ptr<Actor>>> &actors = *CoreLogic::DataProcessing::ActorStorage::getActors();
        if (actors.empty())
        {
            return false;
        }
        for (auto &actorPtr : actors)
        {
            if (actorPtr == nullptr)
            {
                continue;
            }
            Actor &object = *actorPtr;
            if (object.getId() == id_)
            {
                continue;
            }
            /*
             *@note: object needs Hitbox, death Hitboxes should be probably smaller than the actual Sprite,
             *       @proposal: death Hitboxes 75% of Sprite so you dont immediately kill yourself when touching but still
             *                  can't pass through multiple of them when they are side by side
             */
            Rectangle objectHitbox = object.getHitbox();
            if (CheckCollisionRecs(hitbox_, objectHitbox))
            {

                if (object.getCollisionType() == CollisionType::NONE)
                {
                    continue;
                }
                if (object.getCollisionType() == CollisionType::WALKABLE)
                {
                    continue;
                }
                Rectangle collisionRec = GetCollisionRec(hitbox_, objectHitbox);
                if (pa_direction == CoreLogic::UserInterface::Direction::UP)
                {
                    position_.y += collisionRec.height;
                    updateHitbox();
                } else if (pa_direction == CoreLogic::UserInterface::Direction::DOWN)
                {
                    position_.y -= collisionRec.height;
                    updateHitbox();
                } else if (pa_direction == CoreLogic::UserInterface::Direction::LEFT)
                {
                    position_.x += collisionRec.width;
                    updateHitbox();
                } else if (pa_direction == CoreLogic::UserInterface::Direction::RIGHT)
                {
                    position_.x -= collisionRec.width;
                    updateHitbox();
                }
            }

        }
        return false;
    }



CoreLogic::EventManagement::Actors::Drone::Drone(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size,
                                                 int pa_elevation)
        : MovableActor(pa_position, pa_hitbox, pa_id, Actor::CollisionType::NONE, pa_size, true, pa_elevation)
        {

        }

    void Drone::update()
    {
        checkInteraction();
        /*int interactionTypus;
        if  (interaction_ == nullptr)
        {
            interactionTypus = -1;
        } else {
            interactionTypus = interaction_->getType();
        }
        std::cout << interactionTypus << std::endl;*/
        checkAbility();
        /*int abilityTypus;
        if  (ability_ == nullptr)
        {
            abilityTypus = -1;
        } else {
            abilityTypus = ability_->getAbilityType();
        }
        std::cout << abilityTypus << std::endl;
        std::cout <<std::endl;
        std::cout <<std::endl;*/
    }


    void Drone::checkInteraction()
    {
        Rectangle extensionRec = hitbox_;
        switch (primaryDirection_)
        {
            case UserInterface::Direction::RIGHT:
                extensionRec.x += DataProcessing::global_tileSize / 2;
                break;
            case UserInterface::Direction::LEFT:
                extensionRec.x -= DataProcessing::global_tileSize / 2;
                break;
            case UserInterface::Direction::UP:
                extensionRec.y -= DataProcessing::global_tileSize / 2;
                break;
            case UserInterface::Direction::DOWN:
                extensionRec.y += DataProcessing::global_tileSize / 2;
                break;
        }
        /**
         * @Pseudo_Code: getInteractions() not yet existing
         */

        std::vector<std::shared_ptr<Object::Interaction>> &interactions = DataProcessing::ActorStorage::getInteractions()->at(
                elevation_);

        for (auto &interaction: interactions)
        {
            if (interaction == nullptr)
            {
                continue;
            }
            if (interaction->getElevation() == elevation_)
            {
                if (CheckCollisionRecs(extensionRec, interaction->getHitbox()))
                {
                    setInteraction(interaction);
                    return;
                } else if (CheckCollisionRecs(hitbox_, interaction->getHitbox()))
                {
                    setInteraction(interaction);
                    return;
                }
            }
        }
        setInteraction(nullptr);

    }

    void Drone::setInteraction(std::shared_ptr<CoreLogic::EventManagement::Object::Interaction> pa_interaction)
    {
        interaction_ = pa_interaction;
    }

    std::shared_ptr<Object::Interaction> Drone::getInteraction()
    {
        return interaction_;
    }

    void Drone::setAbility(std::shared_ptr<CoreLogic::EventManagement::Object::Ability> pa_ability)
    {
        ability_ = pa_ability;
    }

    std::shared_ptr<CoreLogic::EventManagement::Object::Ability> Drone::getAbility()
    {
        return ability_;
    }


    int Drone::getMaxHealth() const
    {
        return maxHealth_;
    }

    void Drone::setMaxHealth(int pa_maxHealth)
    {
        maxHealth_ = pa_maxHealth;
    }

    void Drone::increaseMaxHealth()
    {
        if (!(maxHealth_ + 2 > 7))
        {
            maxHealth_ += 2;
            increaseCurrentHealth();
            increaseCurrentHealth();
        }
    }

    void Drone::increaseCurrentHealth()
    {
        currentHealth_ += CoreLogic::DataProcessing::DesignConfig::REGENERATION_LIFE;
        if (currentHealth_ > maxHealth_)
        {
            currentHealth_ = maxHealth_;
        }
    }

    void Drone::decreaseCurrentHealth()
    {
        currentHealth_--;
    }

    void Drone::setCurrentHealth(int pa_currentHealth)
    {
        currentHealth_ = pa_currentHealth;
    }

    int Drone::getCurrentHealth() const
    {
        return currentHealth_;
    }


    Drone::DroneType Drone::getDroneType() const
    {
        return currentDroneType_;
    }

    void Drone::setDroneType(Drone::DroneType pa_droneType)
    {
        currentDroneType_ = pa_droneType;
    }


    bool Drone::isDying()
    {
        if (currentDroneState_ == DroneState::DEATH)
        {
            return true;
        } return false;
    }

    bool Drone::canMove()
    {
        if (currentDroneState_ == DroneState::MOVING)
        {
            return true;
        } return false;
    }

    bool Drone::canAct()
    {
        if (ability_ == nullptr || currentDroneState_ != MOVING)
        {
            return false;
        }
        return true;
    }

    bool Drone::canInteract()
    {
        if (interaction_ == nullptr || currentDroneState_ != MOVING)
        {
            return false;
        }
        return true;
    }

    bool Drone::canDeathAbility()
    {
        if (currentDroneState_ == MOVING && currentDroneType_ == DroneType::SCOUT)
        {
            return true;
        }
        return false;
    }

    void Drone::setDroneState(Drone::DroneState pa_droneState)
    {
        switch (currentDroneState_)
        {
            case DEATH:
                if (pa_droneState != DEATH)
                {
                    throw EventException("Drone already dying", false);
                }
                break;
            case JUMP:
                if (pa_droneState != JUMP)
                {
                    throw EventException("Drone jumping", false);
                }
                break;
            case DEATH_ABILITY:
                if (pa_droneState != DEATH_ABILITY)
                {
                    throw EventException("Drone dying with ability", false);
                }
                break;
            case MOVING:
                if (pa_droneState != MOVING)
                {
                    currentDroneState_ = pa_droneState;

                }
                break;
            case ABILITY:
                if(pa_droneState == DEATH || pa_droneState == JUMP)
                {
                    currentDroneState_ = pa_droneState;
                }
                break;
            case INTERACTING:
                if (pa_droneState == DEATH)
                {
                    currentDroneState_ = pa_droneState;
                }
                break;
        }
    }

    Drone::DroneState Drone::getDroneState() const
    {
        return currentDroneState_;
    }

    void Drone::removeDroneState(Drone::DroneState pa_droneState)
    {
        if (currentDroneState_ == DEATH)
        {
            return;
        }
        if (currentDroneState_ == pa_droneState)
        {
            currentDroneState_ = MOVING;
        }
    }

    Drone::Drone(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation,
            int pa_maxHealth, int pa_currentHealth)
            : MovableActor(pa_position, pa_hitbox, pa_id, Actor::CollisionType::NONE, pa_size, true, pa_elevation)
    {
        maxHealth_ = pa_maxHealth;
        currentHealth_ = pa_currentHealth;
    }

}


