//
// Created by Josi on 12.06.2024.
//

#include "Enemy.h"
#include "DesignConfig.h"
#include "data_processing/Store.h"
#include "EventHandler.h"
#include "TilesonUtilities.h"


namespace CoreLogic::EventManagement::Actors
{
    void Enemy::updateTurnCycle()
    {
        if (turnCycles.at(primaryDirection_).second <= 0)
        {

            turn();
        } else
        {
            turnCycles.at(primaryDirection_).second--;
        }
    }


    void Enemy::turn()
    {
        UserInterface::Direction currentDir = primaryDirection_;
        UserInterface::Direction turnOrder[5] = {turnOrder[0] = UserInterface::Direction::UP, turnOrder[1] = UserInterface::Direction::RIGHT, turnOrder[2] = UserInterface::Direction::DOWN, turnOrder[3] = UserInterface::Direction::LEFT, turnOrder[4] = UserInterface::Direction::UP};

        if (!clockwise_)
        {
            turnOrder[1] = UserInterface::Direction::LEFT;
            turnOrder[3] = UserInterface::Direction::RIGHT;
        }
        bool start = false;
        int startIndex = 0;
        int currentIndex = 0;

        do
        {
            if (!start)
            {
                if (turnOrder[currentIndex] == currentDir)
                {
                    start = true;
                    startIndex = currentIndex;
                }
            } else
            {
                if (turnOrder[currentIndex] == currentDir)
                {
                    continue;
                } else if (turnCycles.at(turnOrder[currentIndex]).first != 0)
                {
                    primaryDirection_ = turnOrder[currentIndex];
                    break;
                }
            }
            if (currentIndex != 4)
            {
                currentIndex++;
            }else
            {
                currentIndex = 0;
            }
        } while (currentDir == primaryDirection_ && currentIndex != startIndex);
        turnCycles.at(primaryDirection_).second = turnCycles.at(primaryDirection_).first;

    }

    void Enemy::forceTurn(Vector2 pa_triggerPoint)
    {
        int detectionRadius = CoreLogic::DataProcessing::DesignConfig::COLONIST_RANGE * CoreLogic::DataProcessing::tileSize;
        if (!CheckCollisionPointCircle(pa_triggerPoint, visionOrigin_, static_cast<float>(detectionRadius)))
        {
            return;
        }
        int turnFrames = CoreLogic::DataProcessing::DesignConfig::BELL_TURN_TIME;
        if (abs(pa_triggerPoint.x) >= abs(pa_triggerPoint.y))
        {
            (pa_triggerPoint.x >
                    0) ? primaryDirection_ = UserInterface::Direction::RIGHT : primaryDirection_ = UserInterface::Direction::LEFT;
        } else
        {
            (pa_triggerPoint.y >
                    0) ? primaryDirection_ = UserInterface::Direction::DOWN : primaryDirection_ = UserInterface::Direction::UP;
        }
        turnCycles.at(primaryDirection_).second = turnFrames;
    }

    void Enemy::update()
    {
        if (dead_)
        {
            return;
        }
        if (!visionConnected_)
        {
            updateTurnCycle();
            shiftFrame(0);
        }
        checkVision();
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
        if (player -> getElevation() != elevation_)
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

        (primaryDirection_ == UserInterface::Direction::UP ||
                primaryDirection_ == UserInterface::Direction::RIGHT) ? p2 = {visionOrigin_.x + range,
                visionOrigin_.y - range} : p2 = {visionOrigin_.x - range, visionOrigin_.y + range};

        (primaryDirection_ == UserInterface::Direction::DOWN ||
                primaryDirection_ == UserInterface::Direction::RIGHT) ? p3 = {visionOrigin_.x + range,
                visionOrigin_.y + range} : p3 = {visionOrigin_.x - range, visionOrigin_.y - range};

        DataProcessing::Line visionLines[4];

        visionLines[0] = {visionOrigin_, {playerHitbox.x, playerHitbox.y}};
        visionLines[1] = {visionOrigin_, {playerHitbox.x + playerHitbox.width, playerHitbox.y}};
        visionLines[2] = {visionOrigin_, {playerHitbox.x + playerHitbox.width, playerHitbox.y + playerHitbox.height}};
        visionLines[3] = {visionOrigin_, {playerHitbox.x, playerHitbox.y + playerHitbox.height}};

        bool collides = false;
        bool collisions[4] = {true, true, true, true};
        for (int i = 0; i < 4; i++)
        {
            Vector2 collisionPoint = visionLines[i].p2;
            if (!CheckCollisionPointTriangle(collisionPoint, p1, p2, p3))
            {
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

        if (intersected)
        {
            visionConnected_ = false;
        } else {
            if (!visionConnected_)
            {
                visionConnected_ = true;
                auto &eh = EventHandler::getInstance();
                std::vector<EventEnum> events = {EventManagement::EventEnum::VISION};
                eh.handleEvents(events, getId());
            }
        }


    }

    bool Enemy::checkVisionCollisionObjects(DataProcessing::Line *pa_visionRays, bool *pa_visionCollisions)
    {
        std::vector<std::shared_ptr<Actor>> barriers = CoreLogic::DataProcessing::ActorStorage::getCollidables()->at(elevation_);
        bool *visionCollisions = pa_visionCollisions;

        for (auto &barrier: barriers)
        {
            if (barrier == nullptr)
            {
                continue;
            }
            if (barrier->getElevation() != elevation_)
            {
                continue;
            }
            if (barrier->getCollisionType() == Actor::CollisionType::NONE)
            {
                continue;
            }

            Rectangle barrierHitbox = barrier->getHitbox();

            for (int i = 0; i < 4; ++i)
            {
                if (!visionCollisions[i])
                {
                    continue;
                }
                if (DataProcessing::CheckCollisionLineRec(pa_visionRays[i], barrierHitbox))
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
            std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> pa_objectTurnCycle,
            Vector2 pa_visionPoint) :
            Actor(pa_position, pa_hitbox, pa_objectId, CollisionType::COLLISION, pa_objectSize, true,
                    pa_objectElevation), visionOrigin_(pa_visionPoint), turnCycles(pa_objectTurnCycle)
    {
        primaryDirection_ = pa_objectStartingDirection;
        clockwise_ = pa_objectClockwise;
    }

    bool Enemy::getClockwise() const
    {
        return clockwise_;
    }

    void Enemy::setClockwise(bool pa_clockwise)
    {
        clockwise_ = pa_clockwise;
    }

    bool Enemy::getDead() const
    {
        return dead_;
    }

    void Enemy::setDead(bool pa_dead)
    {
        dead_ = pa_dead;
    }

    std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> Enemy::getTurnCycles() const
    {
        return turnCycles;
    }

    void Enemy::setTurnCycles(std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> pa_turnCycles)
    {
        turnCycles = pa_turnCycles;
    }

    void Enemy::die()
    {

    }

    void Enemy::shiftFrame(int pa_frameShift)
    {
        if (pa_frameShift == 0)
        {
            if (state_ == IDLE && !dead_ && DataProcessing::ticks % 6 == 0)
            {
                sprite_.shiftFrame(pa_frameShift, primaryDirection_);
                return;
            }
        } else {
            if (pa_frameShift != 3 && dead_)
            {
                return;
            }
            sprite_.shiftFrame(pa_frameShift, primaryDirection_);
        }
    }
}