//
// Created by keanu on 9/6/2024.
//

#include "EnemyDisconnectEvent.h"
#include "actors/Enemy.h"
#include "Store.h"


namespace CoreLogic::EventManagement
{
    EnemyDisconnectEvent::EnemyDisconnectEvent(int pa_enemyID): Event(ENEMY_DEATH)
    {
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
            throw std::runtime_error("Enemy not found");
        }
        std::dynamic_pointer_cast<Actors::Enemy>(po_mainActor_)->die();
    }

    void EnemyDisconnectEvent::update()
    {
        if (ticks_ % 3 == 0)
        {
            po_mainActor_ ->shiftFrame(/**@warning: to determine frame shifts*/);
        }
        if (ticks_ >=36)
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