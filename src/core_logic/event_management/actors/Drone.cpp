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
        /**
         *@pseudo_code
         * @Commented the collision since actor and layers not yet fully embedded
         * @todo uncomment when actor and layers function
         **/
        EventHandler &eventHandler = EventHandler::getInstance();

        int tickMult = CoreLogic::DataProcessing::ticks % 3;
        int diagonalSpeed;
        if (CoreLogic::DataProcessing::DesignConfig::DRONE_SPEED == 1)
        {
            diagonalSpeed = (1 - ((int) (tickMult / 2)));
        } else
        {
            diagonalSpeed = ((CoreLogic::DataProcessing::DesignConfig::DRONE_SPEED / 2) +
                             (CoreLogic::DataProcessing::DesignConfig::DRONE_SPEED % 2) + ((int) (tickMult / 2)));
        }
        if (pa_up && !pa_down)
        {
            (pa_right || pa_left) ? position_.y -= diagonalSpeed
                                  : position_.y -= CoreLogic::DataProcessing::DesignConfig::DRONE_SPEED;
            updateHitbox();
            if (checkCollision(CoreLogic::UserInterface::Direction::UP, position_))
            {
                eventHandler.handleEvents({DISCONNECT}, id_);
            }
        }

        if (pa_down && !pa_up)
        {
            (pa_right || pa_left) ? position_.y += diagonalSpeed
                                  : position_.y += CoreLogic::DataProcessing::DesignConfig::DRONE_SPEED;
            updateHitbox();
            if (checkCollision(CoreLogic::UserInterface::Direction::DOWN, {position_.x, position_.y + size_.y}))
            {
                eventHandler.handleEvents({DISCONNECT}, id_);
            }
        }

        if (pa_left && !pa_right)
        {
            (pa_up || pa_down) ? position_.x -= diagonalSpeed
                               : position_.x -= CoreLogic::DataProcessing::DesignConfig::DRONE_SPEED;
            updateHitbox();
            if (checkCollision(CoreLogic::UserInterface::Direction::LEFT, position_))
            {
                eventHandler.handleEvents({DISCONNECT}, id_);
            }
        }

        if (pa_right && !pa_left)
        {
            (pa_up || pa_down) ? position_.x += diagonalSpeed
                               : position_.x += CoreLogic::DataProcessing::DesignConfig::DRONE_SPEED;
            updateHitbox();
            if (checkCollision(CoreLogic::UserInterface::Direction::RIGHT, {position_.x + size_.x, position_.y}))
            {
                eventHandler.handleEvents({DISCONNECT}, id_);
            }
        }
    }

    bool Drone::checkCollision(CoreLogic::UserInterface::Direction pa_direction, Vector2 pa_position)
    {
        /**
         * @pseudo_code TODO: Elevation and Input Handler
         * @brief: This method checks if the Drone is colliding with any Tile or Object on the Tiles that he touches on his
         *         elevation in the movement direction. If the Collision is a death Collision it throws a KillEvent to the
         *         Eventhandler if not it just pushes the player outside of the Hitbox of the collision.
         *         This Method is @recursive, it calls itself for each new tested Tile.
         *
         * @should_return: should return true if collides?
         **/

        /**
         *@note: to be written Func for convenience
         **/
        /*Vector2 tileID = CoreLogic::DataProcessing::coordinatesToTile(pa_position);
        Vector2 startID = tileID;
        Vector2 endID;
        if (pa_direction == CoreLogic::UserInterface::Direction::UP ||
            pa_direction == CoreLogic::UserInterface::Direction::DOWN)
        {
            endID = CoreLogic::DataProcessing::coordinatesToTile({pa_position.x + size_.x, pa_position.y});
        } else if (pa_direction == CoreLogic::UserInterface::Direction::LEFT ||
                   pa_direction == CoreLogic::UserInterface::Direction::RIGHT)
        {
            endID = CoreLogic::DataProcessing::coordinatesToTile({pa_position.x, pa_position.y + size_.y});
        } else
        {
            throw std::runtime_error("Direction not defined");
        }
        std::map<int, std::vector<tson::Layer>> &layers = *CoreLogic::DataProcessing::ActorStorage::getLayers();


        for (auto &layer: layers[elevation_])
        {
            if (!(layer.getType() == tson::LayerType::TileLayer))
            {
                continue;
            }
            do
            {
                tson::Tile *tilePtr = layer.getTileData(static_cast<int>(tileID.x), static_cast<int>(tileID.y));
                if (tilePtr == nullptr)
                {
                    if (pa_direction == CoreLogic::UserInterface::Direction::UP ||
                        pa_direction == CoreLogic::UserInterface::Direction::DOWN)
                    {
                        tileID.x++;
                    } else if (pa_direction == CoreLogic::UserInterface::Direction::LEFT ||
                               pa_direction == CoreLogic::UserInterface::Direction::RIGHT)
                    {
                        tileID.y++;
                    } else
                    {
                        throw std::runtime_error("Invalid Direction");
                    }
                    continue;
                }
                tson::Tile &tile = *tilePtr;

                if (tile.getClassType() == "Wall")
                {

                    tson::Vector2f tilePosition = tile.getPosition({tileID.x, tileID.y});
                    Rectangle tileRec = {
                            tilePosition.x, tilePosition.y, static_cast<float>(tile.getTileSize().x),
                            static_cast<float>(tile.getTileSize().y)
                    };

                    Rectangle collisionRec = GetCollisionRec(hitbox_, tileRec);
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
                if (pa_direction == CoreLogic::UserInterface::Direction::UP ||
                    pa_direction == CoreLogic::UserInterface::Direction::DOWN)
                {
                    tileID.x++;
                } else if (pa_direction == CoreLogic::UserInterface::Direction::LEFT ||
                           pa_direction == CoreLogic::UserInterface::Direction::RIGHT)
                {
                    tileID.y++;
                } else
                {
                    throw std::runtime_error("Invalid Direction");
                }
            } while (tileID.x <= endID.x && tileID.y <= endID.y);
            tileID = startID;


        }

*/
        /**
         *@TODO: Map.getActors() and elevation Handling
         **/

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
                /*
                 *@note: object needs Collision Type probably within Tiled
                 * @note: Death collision probably to be handled outside of event in update func frame after movement
                 * @TODO: Collision Type
                 */
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
        : MovableActor(pa_position, pa_hitbox, pa_id, Actor::CollisionType::NONE, pa_size, true, pa_elevation){}

    void Drone::update()
    {
        checkInteraction();
        checkAbility();
    }


    void Drone::checkInteraction()
    {
        Rectangle extensionRec = hitbox_;
        switch (primaryDirection_)
        {
            case UserInterface::Direction::RIGHT:
                extensionRec.x += DataProcessing::tileSize / 2;
                break;
            case UserInterface::Direction::LEFT:
                extensionRec.x -= DataProcessing::tileSize / 2;
                break;
            case UserInterface::Direction::UP:
                extensionRec.y -= DataProcessing::tileSize / 2;
                break;
            case UserInterface::Direction::DOWN:
                extensionRec.y += DataProcessing::tileSize / 2;
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
        currentHealth_++;
        if (currentHealth_ > maxHealth_)
        {
            currentHealth_ = maxHealth_;
        }
    }

    void Drone::decreaseCurrentHealth()
    {
        currentHealth_--;
        if (currentHealth_ < 1)
        {
            currentHealth_ = 1;
        }
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

}


