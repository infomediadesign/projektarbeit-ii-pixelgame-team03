//
// Created by keanu on 9/6/2024.
//

#include "BellDeathAbilityEvent.h"


    namespace CoreLogic::EventManagement
    {
        BellDeathAbilityEvent::BellDeathAbilityEvent(): DeathAbilityEvent(){}

        void BellDeathAbilityEvent::update()
        {
            if (ticks_ % 3 == 0)
            {
                po_mainActor_ ->shiftFrame(3);
            }

            if (ticks_ >=36)
            {
                throw EventException("Drone disconnected", true);
            }

            ticks_++;
        }

        BellDeathAbilityEvent::~BellDeathAbilityEvent()
        {
            std::vector<std::shared_ptr<Actors::Enemy>> &listeningEnemies = CoreLogic::DataProcessing::ActorStorage::getEnemies()->at(po_mainActor_->getElevation());
            for (auto &enemy: listeningEnemies)
            {
                if (enemy == nullptr)
                {
                    continue;
                }
                if (std::dynamic_pointer_cast<Actors::Enemy>(enemy)->getElevation() != po_mainActor_->getElevation())
                {
                    continue;
                }
                Rectangle hitbox = po_mainActor_ -> getHitbox();
                Vector2 centerPoint = {hitbox.x + hitbox.width / 2, hitbox.y + hitbox.height / 2};
                enemy ->forceTurn(centerPoint);
            }
        }
    } // CoreLogic
// EventManagement