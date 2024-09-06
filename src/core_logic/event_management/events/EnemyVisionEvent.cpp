//
// Created by keanu on 9/6/2024.
//

#include <stdexcept>
#include "EnemyVisionEvent.h"
#include "actors/Enemy.h"
#include "DesignConfig.h"
#include "Store.h"
#include "EventHandler.h"


namespace CoreLogic::EventManagement
{
    EnemyVisionEvent::EnemyVisionEvent(int pa_id) : Event(VISION)
    {
        std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Enemy>>> &enemyPairs = *DataProcessing::ActorStorage::getEnemies();
        bool found = false;
        for (auto &enemyPair : enemyPairs)
        {
            for (auto &enemy : enemyPair.second)
            {
                if (enemy->getId() == pa_id)
                {
                    po_mainActor_ = enemy;
                    found = true;
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
        ticks_ = CoreLogic::DataProcessing::DesignConfig::COLONIST_DETECTION_RATE;
        /**
         * @PseudoCode: no enemy state yet
         * @todo: add enemy state
         */
        std::dynamic_pointer_cast<Actors::Enemy>(po_mainActor_) -> setState(Actors::Enemy::EnemyState::VISION);
        po_player_ = CoreLogic::DataProcessing::ActorStorage::getPlayer();

    }

    void EnemyVisionEvent::update()
    {
        if (!found_)
        {
            lookout();
        } else {
            shoot();
        }

        ticks_--;
    }

    void EnemyVisionEvent::lookout()
    {
        if (!std::dynamic_pointer_cast<Actors::Enemy>(po_mainActor_)->getVisionConnected())
        {
            throw EventException("Fled Vision");
        }

        if (ticks_ % (CoreLogic::DataProcessing::DesignConfig::COLONIST_DETECTION_RATE / 6) == 0)
        {
            po_mainActor_->shiftFrame(/**@warning insert enemy lookout frame*/);
        }
        if (ticks_ == 0)
        {
            found_ = true;
            /**
             * @PseudoCode: no drone state yet
             * @todo: add drone state
             */
            po_player_->setState(Actors::Drone::DroneState::DEATH);
            ticks_ == 24;
        }
    }

    void EnemyVisionEvent::shoot()
    {
        if (ticks_ % 6 == 0)
        {
            po_mainActor_->shiftFrame(/**@warning insert enemy shoot frame*/);
        }

        if (ticks_ == 0)
        {
            throw EventException("Shot Player");
        }
    }

    EnemyVisionEvent::~EnemyVisionEvent()
    {
        std::dynamic_pointer_cast<Actors::Enemy>(po_mainActor_) -> setState(Actors::Enemy::EnemyState::IDLE);
        if (found_)
        {
            auto &eh = EventHandler::getInstance();
            eh.handleEvents({DISCONNECT}, po_player_->getId());
        }
    }
} // CoreLogic
// EventManagement