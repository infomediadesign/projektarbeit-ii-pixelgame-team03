//
// Created by keanu on 9/1/2024.
//

#include "FallingBoulderEvent.h"
#include "EventHandler.h"
#include "actors/Enemy.h"
#include "data_processing/Store.h"
#include "actors/objects/Uplink.h"
#include "SoundHandler.h"


namespace CoreLogic::EventManagement
{
    FallingBoulderEvent::FallingBoulderEvent(std::shared_ptr<Object::Boulder> pa_boulder) : FallingEvent(BOULDER_FALL)
    {
        po_mainActor_ = pa_boulder;
        fallHeight_ = std::dynamic_pointer_cast<Object::Boulder>(po_mainActor_) -> getFallHeight();
    }

    void FallingBoulderEvent::destroy()
    {
        if (ticks_ == 0)
        {
            auto &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
            if (fallHeight_ == 1)
            {
                soundHandler.playSound(SoundHandler::IMPACT_WATER);
            } else {
                soundHandler.playSound(SoundHandler::IMPACT_FLOOR);
            }
            auto& eventHandler = EventHandler::getInstance();
            Rectangle hitbox = po_mainActor_ -> getHitbox();
            std::vector<std::shared_ptr<Actors::Enemy>> &enemies = CoreLogic::DataProcessing::ActorStorage::getEnemies()->at(std::dynamic_pointer_cast<Object::Boulder>(po_mainActor_)->getNewElevation());
            for (auto &enemy: enemies)
            {
                if (enemy == nullptr || enemy -> getDead())
                {
                    continue;
                }
                if (std::dynamic_pointer_cast<Actor>(enemy)->getElevation() !=
                std::static_pointer_cast<Object::Boulder>(po_mainActor_) -> getNewElevation())
                {
                    continue;
                }
                if (CheckCollisionRecs(hitbox, enemy -> getHitbox()))
                {
                    eventHandler.handleEvents({ENEMY_DEATH}, enemy -> getId());
                }
            }
        }
        if (ticks_ % 5 == 0)
        {
            po_mainActor_ -> shiftFrame(1);
        }

        if (ticks_ >= 20)
        {

            throw EventException("Boulder Destroyed", true);
        }
        ticks_++;
    }

    void FallingBoulderEvent::fall()
    {
        FallingEvent::fall();
        if (fallenHeight_ == 1)
        {
            int newElevation = 0;
            if (po_mainActor_ ->getElevation() > 0)
            {
                newElevation = po_mainActor_ ->getElevation() - 1 ;
            } else {
                newElevation = 0;
                po_mainActor_->setVisible(false);
            }
            CoreLogic::DataProcessing::ActorStorage::changeDrawingElevation(po_mainActor_, newElevation);
        }
    }
} // CoreLogic
// EventManagement