//
// Created by keanu on 9/6/2024.
//

#include "BellDeathAbilityEvent.h"
#include "SoundHandler.h"


namespace CoreLogic::EventManagement
    {
        BellDeathAbilityEvent::BellDeathAbilityEvent(): DeathAbilityEvent()
        {
            auto &soundHandler = EventManagement::SoundHandler::getInstance();
            soundHandler.playSound(SoundHandler::BELL);
            animationSpeed_ = DataProcessing::DesignConfig::BELL_DEATH_SPEED;
            animationLength_ = po_mainActor_->getSprite().getFrameAmount(3) * animationSpeed_ - 1;
        }

        void BellDeathAbilityEvent::update()
        {
            if (ticks_ % animationSpeed_ == 0)
            {
                po_mainActor_ ->shiftFrame(3);
            }

            if (ticks_ >= animationLength_)
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
            std::shared_ptr<Actors::Drone> drone = std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_);
            drone -> decreaseCurrentHealth();
            if (drone -> getCurrentHealth() <= 0)
            {
                CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::DEATH);
            } else
            {
                DataProcessing::StateMachine::changeState(DataProcessing::DRONE_SELECTION);
            }
        }
    } // CoreLogic
// EventManagement