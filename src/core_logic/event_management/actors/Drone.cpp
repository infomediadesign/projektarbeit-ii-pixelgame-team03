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
#include "../../../designConfig"

void CoreLogic::EventManagement::Actors::Drone::move(bool pa_up, bool pa_down, bool pa_left, bool pa_right)
{
    /**
     *@pseudo_code
     * @Commented the collision since actor and layers not yet fully embedded
     * @todo uncomment when actor and layers function
     **/
     EventHandler& eventHandler = EventHandler::getInstance();

    int tickMult = CoreLogic::DataProcessing::ticks % 3;
    int diagonalSpeed;
    if (GameSpace::DesignConfig::DRONE_SPEED == 1)
    {
        diagonalSpeed = (1 - ((int) (tickMult / 2)));
    } else {
        diagonalSpeed = ((GameSpace::DesignConfig::DRONE_SPEED / 2) + (GameSpace::DesignConfig::DRONE_SPEED % 2) + ((int) (tickMult / 2)));
    }
    if (pa_up && !pa_down)
    {
        (pa_right || pa_left) ? position_.y -= diagonalSpeed : position_.y -= GameSpace::DesignConfig::DRONE_SPEED;
        adjustOutOfBounds();
        updateHitbox();
        if (checkCollision(CoreLogic::UserInterface::Direction::UP, position_))
        {
            eventHandler.handleEvents({DISCONNECT}, id_);
        }
    }

    if (pa_down && !pa_up)
    {
        (pa_right || pa_left) ? position_.y += diagonalSpeed : position_.y += GameSpace::DesignConfig::DRONE_SPEED;
        adjustOutOfBounds();
        updateHitbox();
        if (checkCollision(CoreLogic::UserInterface::Direction::DOWN, {position_.x, position_.y + size_.y}))
        {
            eventHandler.handleEvents({DISCONNECT}, id_);
        }
    }

    if (pa_left && !pa_right)
    {
        (pa_up || pa_down) ? position_.x -= diagonalSpeed : position_.x -= GameSpace::DesignConfig::DRONE_SPEED;
        adjustOutOfBounds();
        updateHitbox();
        if (checkCollision(CoreLogic::UserInterface::Direction::LEFT, position_))
        {
            eventHandler.handleEvents({DISCONNECT}, id_);
        }
    }

    if (pa_right && !pa_left)
    {
        (pa_up || pa_down) ? position_.x += diagonalSpeed : position_.x += GameSpace::DesignConfig::DRONE_SPEED;
        adjustOutOfBounds();
        updateHitbox();
        if (checkCollision(CoreLogic::UserInterface::Direction::RIGHT, {position_.x + size_.x, position_.y}))
        {
            eventHandler.handleEvents({DISCONNECT}, id_);
        }
    }
}



bool CoreLogic::EventManagement::Actors::Drone::checkCollision(CoreLogic::UserInterface::Direction pa_direction, Vector2 pa_position)
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
    Vector2 tileID = CoreLogic::DataProcessing::coordinatesToTile(pa_position);
    Vector2  startID = tileID;
    Vector2 endID;
    if (pa_direction == CoreLogic::UserInterface::Direction::UP || pa_direction == CoreLogic::UserInterface::Direction::DOWN)
    {
        endID = CoreLogic::DataProcessing::coordinatesToTile({pa_position.x + size_.x, pa_position.y});
    } else if (pa_direction == CoreLogic::UserInterface::Direction::LEFT || pa_direction == CoreLogic::UserInterface::Direction::RIGHT) {
        endID = CoreLogic::DataProcessing::coordinatesToTile({pa_position.x, pa_position.y + size_.y});
    } else {
        throw std::runtime_error("Direction not defined");
    }
    std::map<int, std::vector<tson::Layer>>& layers = *CoreLogic::DataProcessing::ActorStorage::getLayers();

    /**
     *@note: yet unclear how to get the layers
     **/
    for(auto &layer: layers[elevation_])
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
            /**
             *@todo: to be redefined as not Wall
             **/
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


    /**
     *@TODO: Map.getActors() and elevation Handling
     **/
    bool dies = false;
    std::map<int, std::vector<std::shared_ptr<Actor>>> &actors = *CoreLogic::DataProcessing::ActorStorage::getActors();
    if (!(actors.find(elevation_) != actors.end()))
    {
        return false;
    }
    for (auto &objectPtr : actors[elevation_])
    {
        if (objectPtr == nullptr)
        {
            continue;
        }
        Actor &object = *objectPtr;
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
            if (object.getCollisionType() == CollisionType::DEATH)
            {
                dies = true;
            }
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
    return dies;
}



CoreLogic::EventManagement::Actors::Drone::Drone(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
                                                 CollisionType pa_collisionType, Vector2 pa_size, bool pa_visible,
                                                 int pa_elevation)
        : MovableActor(pa_position, pa_hitbox, pa_id, pa_collisionType, pa_size, pa_visible, pa_elevation)
{
    /**
     * @todo: remove/change path when drones are implemented and can be switched etc.
     */
    sprite_ = CoreLogic::UserInterface::Sprite("assets/graphics/hive_ARTI_spritesheet-worker-drone_2024-07-13.png", 38, 38,
                                               {{},{
                                                       CoreLogic::UserInterface::AnimationState{0, 7, {0, 0}},
                       CoreLogic::UserInterface::AnimationState{1, 7, {0, 0}},
                      CoreLogic::UserInterface::AnimationState{2, 8, {0, 0}},
                       CoreLogic::UserInterface::AnimationState{3, 8, {0, 0}}}});
}

int CoreLogic::EventManagement::Actors::Drone::getMaxHealth() const {
    return maxHealth_;
}

int CoreLogic::EventManagement::Actors::Drone::getCurrentHealth() const
{
    return currentHealth_;
}

void CoreLogic::EventManagement::Actors::Drone::inceaseMaxHealth()
{
    if (!(maxHealth_ + 2 > 7))
    {
        maxHealth_ += 2;
        increaseCurrentHealth();
        increaseCurrentHealth();
    }
}

void CoreLogic::EventManagement::Actors::Drone::increaseCurrentHealth()
{
    currentHealth_++;
    if (currentHealth_ > maxHealth_)
    {
        currentHealth_ = maxHealth_;
    }
}

void CoreLogic::EventManagement::Actors::Drone::decreaseCurrentHealth()
{
    currentHealth_--;
    if (currentHealth_ < 1)
    {
        currentHealth_ = 1;
    }
}

bool CoreLogic::EventManagement::Actors::Drone::canInteract()
{
    if (interaction_ == nullptr)
    {
        return false;
    }
    return true;
}

bool CoreLogic::EventManagement::Actors::Drone::canAct()
{
    if (ability_ == nullptr)
    {
        return false;
    }
    return true;
}

void CoreLogic::EventManagement::Actors::Drone::update()
{

}

void CoreLogic::EventManagement::Actors::Drone::checkInteraction()
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
    std::vector<std::shared_ptr<Actor>> &interactions = DataProcessing::ActorStorage::getInteractions();
    for (auto &interaction : interactions)
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
            } else if (CheckCollisionRecs(hitbox_, interaction->getHitbox())) {
                setInteraction(interaction);
                return;
            }
        }
    }
    setInteraction(nullptr);

}
void CoreLogic::EventManagement::Actors::Drone::setInteraction(std::shared_ptr<CoreLogic::EventManagement::Object::Interaction> pa_interaction)
{
    interaction_ = pa_interaction;
}

void CoreLogic::EventManagement::Actors::Drone::setAbility(std::shared_ptr<CoreLogic::EventManagement::Object::Ability> pa_ability)
{
    ability_ = pa_ability;
}

std::shared_ptr <CoreLogic::EventManagement::Object::Interaction> CoreLogic::EventManagement::Actors::Drone::getInteraction()
{
    return interaction_;
}

std::shared_ptr <CoreLogic::EventManagement::Object::Ability> CoreLogic::EventManagement::Actors::Drone::getAbility()
{
    return ability_;
}

CoreLogic::EventManagement::Actors::Drone::DroneType CoreLogic::EventManagement::Actors::Drone::getDroneType() const
{
    return currentDroneType_;
}

void CoreLogic::EventManagement::Actors::Drone::setMaxHealth(int pa_maxHealth)
{
maxHealth_ = pa_maxHealth;
}

void CoreLogic::EventManagement::Actors::Drone::setCurrentHealth(int pa_currentHealth)
{
currentHealth_ = pa_currentHealth;
}

void CoreLogic::EventManagement::Actors::Drone::setDroneType(
        CoreLogic::EventManagement::Actors::Drone::DroneType pa_droneType)
{
currentDroneType_ = pa_droneType;
}




