//
// Created by keanu on 9/6/2024.
//

#include <stdexcept>
#include "EnemyVisionEvent.h"
#include "actors/Enemy.h"

namespace CoreLogic
{
    namespace EventManagement
    {
        EnemyVisionEvent::EnemyVisionEvent(int pa_id) : Event(VISION)
        {
            std::map<int, std::vector<std::shared_ptr<Actors::Enemy>>> enemyPairs = DataProcessing::ActorStorage::getEnemies();
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

        }

        void EnemyVisionEvent::update()
        {
            
        }
    } // CoreLogic
} // EventManagement