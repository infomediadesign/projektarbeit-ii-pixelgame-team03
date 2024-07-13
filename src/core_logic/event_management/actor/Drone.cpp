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

void CoreLogic::EventManagement::Actors::Drone::move(bool pa_up, bool pa_down, bool pa_left, bool pa_right)
{
    /**
     *@pseudo_code
     * @Commented the collision since actor and layers not yet fully embedded
     * @todo uncomment when actor and layers function
     **/
     EventHandler& eventHandler = EventHandler::getInstance();

    if (pa_up && !pa_down)
    {
        (pa_right || pa_left) ? position_.y -= 2 : position_.y -= 3;
        adjustOutOfBounds();
        updateHitbox();
        if (checkCollision(CoreLogic::UserInterface::Direction::UP, position_))
        {
            eventHandler.handleEvents({DISCONNECT}, id_);
        }
    }

    if (pa_down && !pa_up)
    {
        (pa_right || pa_left) ? position_.y += 2 : position_.y += 3;
        adjustOutOfBounds();
        updateHitbox();
        if (checkCollision(CoreLogic::UserInterface::Direction::DOWN, {position_.x, position_.y + size_.y}))
        {
            eventHandler.handleEvents({DISCONNECT}, id_);
        }
    }

    if (pa_left && !pa_right)
    {
        (pa_up || pa_down) ? position_.x -= 2 : position_.x -= 3;
        adjustOutOfBounds();
        updateHitbox();
        if (checkCollision(CoreLogic::UserInterface::Direction::LEFT, position_))
        {
            eventHandler.handleEvents({DISCONNECT}, id_);
        }
    }

    if (pa_right && !pa_left)
    {
        (pa_up || pa_down) ? position_.x += 2 : position_.x += 3;
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
        do
        {
            tson::Tile* tilePtr = layer.getTileData(static_cast<int>(tileID.x), static_cast<int>(tileID.y));
            if (tilePtr == nullptr)
            {
                continue;
            }
            tson::Tile& tile = *tilePtr;
            /**
             *@todo: to be redefined as not Wall
             **/
            if (tile.getClassType() == "Wall")
            {

                tson::Vector2f tilePosition = tile.getPosition({tileID.x, tileID.y});
                Rectangle tileRec = {tilePosition.x, tilePosition.y, static_cast<float>(tile.getTileSize().x),
                                     static_cast<float>(tile.getTileSize().y)};

                Rectangle collisionRec = GetCollisionRec(hitbox_, {static_cast<float>(tileRec.x),
                                                                   static_cast<float>(tileRec.y),
                                                                   static_cast<float>(tileRec.width),
                                                                   static_cast<float>(tileRec.height)});
                if (pa_direction == CoreLogic::UserInterface::Direction::UP)
                {
                    position_.y += collisionRec.height;
                    updateHitbox();
                } else if (pa_direction == CoreLogic::UserInterface::Direction::DOWN) {
                    position_.y -= collisionRec.height;
                    updateHitbox();
                } else if (pa_direction == CoreLogic::UserInterface::Direction::LEFT) {
                    position_.x += collisionRec.width;
                    updateHitbox();
                } else if (pa_direction == CoreLogic::UserInterface::Direction::RIGHT) {
                    position_.x -= collisionRec.width;
                    updateHitbox();
                }
            }
            if (pa_direction == CoreLogic::UserInterface::Direction::UP || pa_direction == CoreLogic::UserInterface::Direction::DOWN)
            {
                tileID.x++;
            } else if (pa_direction == CoreLogic::UserInterface::Direction::LEFT || pa_direction == CoreLogic::UserInterface::Direction::RIGHT) {
                tileID.y++;
            } else {
                throw std::runtime_error("Invalid Direction");
            }
        } while (tileID.x <= endID.x && tileID.y <= endID.y);


    }


    /**
     *@TODO: Map.getActors() and elevation Handling
     **/
    bool dies = false;
    std::map<int, std::vector<std::shared_ptr<Actor>>> &actors = *CoreLogic::DataProcessing::ActorStorage::getActors();

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
            return dies;
        }

    }
    /**
     * @note: I think this was trying to account for all tiles, but is very unnecessary
     *
    Vector2 newPosition = pa_position;
    Vector2 positionInvers = {position_.x + size_.x, position_.y + size_.y};
    auto tileSize = static_cast<float>(CoreLogic::DataProcessing::tileSize);
    if (pa_direction == Direction::UP && size_.x > (pa_position.x - position_.x))
    {
        newPosition.x += tileSize;
    } else if (pa_direction == Direction::LEFT && size_.y > (pa_position.y - position_.y)) {
        newPosition.y += tileSize;
    } else if (pa_direction == Direction::DOWN && size_.x > (positionInvers.x - pa_position.x)) {
        newPosition.x -= tileSize;
    } else if (pa_direction == Direction::RIGHT && size_.y > (positionInvers.y - pa_position.y)) {
        newPosition.y -= tileSize;
    }

    dies = checkCollision(pa_direction, newPosition);
*/
    return dies;
}



CoreLogic::EventManagement::Actors::Drone::Drone(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
                                                 CollisionType pa_collisionType, Vector2 pa_size, bool pa_visible,
                                                 int pa_elevation)
        : MovableActor(pa_position, pa_hitbox, pa_id, pa_collisionType, pa_size, pa_visible, pa_elevation)
{
    sprite_ = CoreLogic::UserInterface::Sprite("assets/graphics/anim_sprite.png", 32, 32,
                                               {{},{
                                                       CoreLogic::UserInterface::AnimationState{0, 3},
                       CoreLogic::UserInterface::AnimationState{1, 3},
                      CoreLogic::UserInterface::AnimationState{2, 3},
                       CoreLogic::UserInterface::AnimationState{3, 3}}});
}


