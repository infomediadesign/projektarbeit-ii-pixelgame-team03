//
// Created by keanu on 5/23/2024.
//

#include "Drone.h"
#include "raylib.h"
#include "../../../tileson.h"
#include "event_management/EventHandler.h"
#include "data_processing/TilesonUtilities.h"
#include "data_processing/Store.h"

void CoreLogic::EventManagement::Actors::Drone::move(bool pa_up, bool pa_down, bool pa_left, bool pa_right)
{
    /**
     *@pseudo_code
     * @should be functioning
     **/
     EventHandler& eventHandler = EventHandler::getInstance();

    if (pa_up && !pa_down)
    {
        (pa_right || pa_left) ? position_.x -= 2 : position_.x -= 3;
        if (checkCollision(Direction::UP, position_))
        {
            eventHandler.handleEvents({DISCONNECT}, id_);
        }
    }

    if (pa_down && !pa_up)
    {
        (pa_right || pa_left) ? position_.x += 2 : position_.x += 3;
        if (checkCollision(Direction::DOWN, position_))
        {
            eventHandler.handleEvents({DISCONNECT}, id_);
        }
    }

    if (pa_left && !pa_right)
    {
        (pa_up || pa_down) ? position_.y -= 2 : position_.y -= 3;
        if (checkCollision(Direction::LEFT, position_))
        {
            eventHandler.handleEvents({DISCONNECT}, id_);
        }
    }

    if (pa_right && !pa_left)
    {
        (pa_up || pa_down) ? position_.y += 2 : position_.y += 3;
        if (checkCollision(Direction::RIGHT, position_))
        {
            eventHandler.handleEvents({DISCONNECT}, id_);
        }
    }
}



bool CoreLogic::EventManagement::Actors::Drone::checkCollision(Direction pa_direction, Vector2 pa_position)
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
    std::map<int, std::vector<tson::Layer>>& layers = *CoreLogic::DataProcessing::ActorStorage::getLayers();

    /**
     *@note: yet unclear how to get the layers
     **/
    for(auto &layer: layers[elevation_])
    {
        tson::Tile &tile = *layer.getTileData(static_cast<int>(tileID.x), static_cast<int>(tileID.y));
        /**
         *@todo: to be redefined as not Wall
         **/
        if (tile.getClassType() == "Wall")
        {
            tson::Rect drawingRect = tile.getDrawingRect();
            Rectangle collisionRec = GetCollisionRec(hitbox_, {static_cast<float>(drawingRect.x),
                                                              static_cast<float>(drawingRect.y),
                                                              static_cast<float>(drawingRect.width),
                                                              static_cast<float>(drawingRect.height)});
            if (pa_direction == Direction::UP)
            {
                position_.y += collisionRec.height;
            } else if (pa_direction == Direction::DOWN)
            {
                position_.y -= collisionRec.height;
            } else if (pa_direction == Direction::LEFT)
            {
                position_.x += collisionRec.width;
            } else if (pa_direction == Direction::RIGHT)
            {
                position_.x -= collisionRec.width;
            }
            return false;
        }
    }

    /**
     *@TODO: Map.getActors() and elevation Handling
     **/
    bool dies = false;
    std::map<int, std::vector<std::shared_ptr<Actor>>> &actors = *CoreLogic::DataProcessing::ActorStorage::getActors();

    for (auto &objectPtr : actors[elevation_])
    {

        Actor &object = *objectPtr;
        /**
         *@note: object needs Hitbox, death Hitboxes should be probably smaller than the actual Sprite,
         *       @proposal: death Hitboxes 75% of Sprite so you dont immediately kill yourself when touching but still
         *                  can't pass through multiple of them when they are side by side
         **/
        Rectangle objectHitbox = object.getHitbox();
        if (CheckCollisionRecs(hitbox_, objectHitbox))
        {
            /**
             *@note: object needs Collision Type probably within Tiled
             * @note: Death collision probably to be handled outside of event in update func frame after movement
             * @TODO: Collision Type
             **/
            if (object.getCollisionType() == CollisionType::DEATH)
            {
                dies = true;
            }
            Rectangle collisionRec = GetCollisionRec(hitbox_, objectHitbox);
            if (pa_direction == Direction::UP)
            {
                position_.y += collisionRec.height;
            } else if (pa_direction == Direction::DOWN)
            {
                position_.y -= collisionRec.height;
            } else if (pa_direction == Direction::LEFT)
            {
                position_.x += collisionRec.width;
            } else if (pa_direction == Direction::RIGHT)
            {
                position_.x -= collisionRec.width;
            }
            return dies;
        }

    }
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

    return dies;
}

Vector2 CoreLogic::EventManagement::Actors::Drone::getPosition()
{
    return position_;
}