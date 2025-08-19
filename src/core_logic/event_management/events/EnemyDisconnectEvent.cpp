//
// Created by keanu on 9/6/2024.
//

#include "EnemyDisconnectEvent.h"
#include "actors/Enemy.h"
#include "data_processing/Store.h"
#include "SoundHandler.h"


namespace CoreLogic::EventManagement
{
    EnemyDisconnectEvent::EnemyDisconnectEvent(int pa_enemyID): Event(ENEMY_DEATH)
    {
        auto &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
        soundHandler.playSound(SoundHandler::DEATH_HUMAN);
        std::map<int, std::vector<std::shared_ptr<Actors::Enemy>>> &enemyPairs = *DataProcessing::ActorStorage::getEnemies();
        bool found= false;
        for (auto &enemyPair : enemyPairs)
        {
            for ( auto &enemy : enemyPair.second)
            {
                if (enemy == nullptr)
                {
                    continue;
                }
                if (enemy->getId() == pa_enemyID)
                {
                    found = true;
                    po_mainActor_ = enemy;
                    break;
                }
            }
            if (found)
            {
                break;
            }
        }
        if (!found)
        {
            throw EventException("Enemy not found", false);
        }
        std::dynamic_pointer_cast<Actors::Enemy>(po_mainActor_)->setDead(true);
        enemyDeathFrames_ = po_mainActor_->getSprite().getFrameAmount(3);
        animationSpeed_ = DataProcessing::DesignConfig::ENEMY_DEATH_SPEED;
        animationLength_ = enemyDeathFrames_ * animationSpeed_-1;
    }

    void EnemyDisconnectEvent::update()
    {
        if (ticks_ % animationSpeed_ == 0)
        {
            po_mainActor_ ->shiftFrame(3);
        }
        if (ticks_ >=animationLength_)
        {
            throw EventException("Drone disconnected", true);
        }

        ticks_++;
    }

    EnemyDisconnectEvent::~EnemyDisconnectEvent()
    {
        po_mainActor_ ->setVisible(false);
        po_mainActor_ ->setCollisionType(Actor::CollisionType::NONE);
    }
} // CoreLogic
// EventManagement