//
// Created by keanu on 5/23/2024.
//

#include "Player.h"
#include "raylib.h"
#include "../../tileson.h"

void CoreLogic::EventManagement::Player::move(bool pa_up, bool pa_down, bool pa_left, bool pa_right)
{
    /**
     *@pseudo_code TODO: Code
     **/

    if (pa_up && !pa_down)
    {
        (pa_right || pa_left) ? position_.x -= 2 : position_.x -= 3;
        checkCollision(UP, position_);
    }

    if (pa_down && !pa_up)
    {
        (pa_right || pa_left) ? position_.x += 2 : position_.x += 3;
        checkCollision(DOWN, positionInvers_);
    }

    if (pa_left && !pa_right)
    {
        (pa_up || pa_down) ? position_.y -= 2 : position_.y -= 3;
        checkCollision(LEFT, position_);
    }

    if (pa_right && !pa_left)
    {
        (pa_up || pa_down) ? position_.y += 2 : position_.y += 3;
        checkCollision(RIGHT, positionInvers_);
    }
}

void CoreLogic::EventManagement::Player::checkCollision(Direction pa_direction, Vector2 pa_position)
{
    /**
     * @pseudo_code TODO: Code
     * @brief: This method checks if the Player is colliding with any Tile or Object on the Tiles that he touches on his
     *         elevation in the movement direction. If the Collision is a death Collision it throws a KillEvent to the
     *         Eventhandler if not it just pushes the player outside of the Hitbox of the collision.
     *         This Method is @recursive, it calls itself for each new tested Tile.
     **/

    /**
     *@note: to be written Func for convenience
     **/
    Vector2 tileID = getTileFromCoordinates(pa_position);


    for(auto layer: layers(elevation_))
    {
        tson::Tile &tile = *layer.getTileData(static_cast<int>(tileID.x), static_cast<int>(tileID.y));
        if (tile.getClassType() == "Wall")
        {
            tson::Rect drawingRect = tile.getDrawingRect();
            Rectangle collisionRec = GetCollisionRec(hitbox, {static_cast<float>(drawingRect.x),
                                                              static_cast<float>(drawingRect.y),
                                                              static_cast<float>(drawingRect.width),
                                                              static_cast<float>(drawingRect.height)});
            if (pa_direction == UP)
            {
                position_.y += collisionRec.height;
            } else if (pa_direction == DOWN)
            {
                position_.y -= collisionRec.height;
            } else if (pa_direction == LEFT)
            {
                posotion_.x += collisionRec.width;
            } else if (pa_direction == RIGHT)
            {
                position_.x -= collisionRec.width;
            }
            return;
        }
    }
    Actor* objectPtr = Level.getActors(elevation_).get(tileID);
    if (objectPtr != nullptr)
    {
        Actor &object = *objectPtr;
        Rectangle objectHitbox = object.getHitbox();
        if (CheckCollisionRecs(hitbox, objectHitbox))
        {
            if (object.getCollisionType() == "Kill")
            {
                /**
                 *@note: EventHandler to be made static?
                 **/
                EventManager.handleEvent((int)killEvent);
                return;
            }
            Rectangle collisionRec = GetCollisionRec(hitbox, objectHitbox);
            if (pa_direction == UP)
            {
                position_.y += collisionRec.height;
            } else if (pa_direction == DOWN)
            {
                position_.y -= collisionRec.height;
            } else if (pa_direction == LEFT)
            {
                posotion_.x += collisionRec.width;
            } else if (pa_direction == RIGHT)
            {
                position_.x -= collisionRec.width;
            }
            return;
        }

    }
    Vector2 newPosition = pa_position;
    if (pa_direction == UP && !(size_.x <= (pa_position.x - position_.x)))
    {
        newPosition.x += tileSize;
    } else if (pa_direction == LEFT && !(size_.y <= (pa_position.y - position_.y))) {
        newPosition.y += tileSize;
    } else if (pa_direction == DOWN && !(size_.x <= (positionInvers_.x - pa_position.x))) {
        newPosition.x -= tileSize;
    } else if (pa_direction == RIGHT && !(size_.y <= (positionInvers_.y - pa_position.y))) {
        newPosition.y -= tileSize;
    }
    checkCollision(pa_direction, newPosition);
    return;
}
