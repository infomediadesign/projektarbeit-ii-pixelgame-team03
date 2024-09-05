//
// Created by Josi on 12.06.2024.
//

#include "Enemy.h"
#include "DesignConfig.h"
#include "Store.h"
#include "EventHandler.h"


namespace CoreLogic::EventManagement::Actors
{
    void Enemy::updateTurnCycle()
    {
        if (turnCyles_.at(primaryDirection_).second <= 0)
        {
            turn();
        } else {
            turnCyles_.at(primaryDirection_).second--;
        }
    }


    void Enemy::turn()
    {
        UserInterface::Direction currentDir = primaryDirection_;
        UserInterface::Direction turnOrder[5] = {
                turnOrder[0] = UserInterface::Direction::UP,
                turnOrder[1] = UserInterface::Direction::RIGHT,
                turnOrder[2] = UserInterface::Direction::DOWN,
                turnOrder[3] = UserInterface::Direction::LEFT,
                turnOrder[4] = UserInterface::Direction::UP
        };

        if (!clockwise_)
        {
            turnOrder[1] = UserInterface::Direction::LEFT;
            turnOrder[3] = UserInterface::Direction::RIGHT;
        }
        bool start = false;
        int currentIndex = 0;

        do
        {
            if (!start)
            {
                if (turnOrder[currentIndex] == currentDir)
                {
                    start = true;
                }
            } else {
                if (turnOrder[currentIndex] == currentDir)
                {
                    continue;
                } else if (turnCyles_.at(turnOrder[currentIndex]).first != 0) {
                    primaryDirection_ = turnOrder[currentIndex];
                    turnCyles_.at(primaryDirection_).second = turnCyles_.at(primaryDirection_).first;
                    break;
                }
            }
            (currentIndex < 5) ? (currentIndex++) : currentIndex = 0;
        } while (currentDir == primaryDirection_);

    }

    void Enemy::forceTurn(Vector2 pa_triggerPoint)
    {
        int turnFrames = CoreLogic::DataProcessing::DesignConfig::BELL_TURN_TIME;
        if (abs(pa_triggerPoint.x) >= abs(pa_triggerPoint.y))
        {
            (pa_triggerPoint.x > 0) ? primaryDirection_ = UserInterface::Direction::RIGHT : primaryDirection_ = UserInterface::Direction::LEFT;
        } else {
            (pa_triggerPoint.y > 0) ? primaryDirection_ = UserInterface::Direction::DOWN : primaryDirection_ = UserInterface::Direction::UP;
        }
        turnCyles_.at(primaryDirection_).second = turnFrames;
    }

    void Enemy::update()
    {

    }

    void Enemy::checkVision()
    {
        int range = CoreLogic::DataProcessing::DesignConfig::COLONIST_RANGE * CoreLogic::DataProcessing::tileSize;
        auto player = CoreLogic::DataProcessing::ActorStorage::getPlayer();
        Rectangle playerHitbox = player->getHitbox();

        if (player == nullptr)
        {
            visionConnected_ = false;
            return;
        }
        if (!(CheckCollisionCircleRec(visionOrigin_, static_cast<float>(range), playerHitbox)))
        {
            visionConnected_ = false;
            return;
        }
        Vector2 p1 = visionOrigin_;
        Vector2 p2;
        Vector2 p3;

        (primaryDirection_ == UserInterface::Direction::UP || primaryDirection_ == UserInterface::Direction::RIGHT) ?
        p2 = {visionOrigin_.x + range, visionOrigin_.y - range} : p2 = {visionOrigin_.x - range, visionOrigin_.y + range};

        (primaryDirection_ == UserInterface::Direction::DOWN || primaryDirection_ == UserInterface::Direction::RIGHT) ?
        p3 = {visionOrigin_.x + range, visionOrigin_.y + range} : p3 = {visionOrigin_.x - range, visionOrigin_.y - range};

        Ray visionLines[4];

        Vector3 rayVisionOrigin = {visionOrigin_.x, visionOrigin_.y, 0};
        visionLines[0] = {rayVisionOrigin, {hitbox_.x, hitbox_.y, 0}};
        visionLines[1] = {rayVisionOrigin, {hitbox_.x + hitbox_.width, hitbox_.y, 0}};
        visionLines[2] = {rayVisionOrigin, {hitbox_.x + hitbox_.width, hitbox_.y + hitbox_.height, 0}};
        visionLines[3] = {rayVisionOrigin, {hitbox_.x, hitbox_.y + hitbox_.height, 0}};

        bool collides = false;
        bool collisions[4] = {true, true, true, true};

        for (int i = 0; i < 4; i++)
        {
            Vector2 collisionPoint = {visionLines[i].direction.x, visionLines[i].direction.y};
            if (!CheckCollisionPointTriangle(collisionPoint, p1, p2, p3))
            {
                visionLines[i] = {{-1,-1,-1}, {-2,-1,-1}};
                collisions[i] = false;
                continue;
            }
            collides = true;
        }

        if (!collides)
        {
            visionConnected_ = false;
            return;
        }

        bool intersected = checkVisionCollisionObjects(visionLines, collisions);

        if (!intersected)
        {
            visionConnected_ = false;
        } else {
            if (!visionConnected_)
            {
                visionConnected_ = true;
                auto& eh = EventHandler::getInstance();
                eh.handleEvents({VISION}, getId());
            }
        }

    }

    bool Enemy::checkVisionCollisionObjects(Ray *pa_visionRays, bool *pa_visionCollisions)
    {
        std::vector<std::shared_ptr<Actor>> barriers = CoreLogic::DataProcessing::ActorStorage::getBarriers().at(elevation_);
        bool *visionCollisions = pa_visionCollisions;

        for (auto barrier : barriers)
        {
            if (barrier == nullptr)
            {
                continue;
            }
            if (barrier->getCollisionType() == Actor::CollisionType::NONE)
            {
                continue;
            }

            Rectangle barrierRec = barrier->getHitbox();
            BoundingBox barrierHitbox = {{barrierRec.x, barrierRec.y,0}, {barrierRec.x + barrierRec.width, barrierRec.y + barrierRec.height,0}};

            for (int i = 0; i < 4; ++i)
            {
                if (!visionCollisions[i])
                {
                    continue;
                }
                if (GetRayCollisionBox(pa_visionRays[i], barrierHitbox).hit)
                {
                    visionCollisions[i] = false;
                }
            }
        }
        for (int i = 0; i < 4; ++i)
        {
            if (pa_visionCollisions[i])
            {
                return false;
            }
        }
        return true;
    }

    Enemy::Enemy(Vector2 pa_position, Rectangle pa_hitbox, int pa_objectId, Vector2 pa_objectSize,
                 int pa_objectElevation, bool pa_objectClockwise,
                 CoreLogic::UserInterface::Direction pa_objectStartingDirection,
                 std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> pa_objectTurnCycle, Vector2 pa_visionPoint): Actor(pa_position, pa_hitbox, pa_objectId, CollisionType::COLLISION, pa_objectSize, true, pa_objectElevation),
                                                                                                                                 visionOrigin_(pa_visionPoint), turnCyles_(pa_objectTurnCycle)
    {
        primaryDirection_ = pa_objectStartingDirection;
        clockwise_ = pa_objectClockwise;
    }
}