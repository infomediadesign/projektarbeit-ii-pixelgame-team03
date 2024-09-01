//
// Created by keanu on 9/1/2024.
//

#include "FallingBoulderEvent.h"
#include "EventHandler.h"


namespace CoreLogic::EventManagement
{
    FallingBoulderEvent::FallingBoulderEvent(std::shared_ptr<Boulder> pa_boulder) : FallingEvent()
    {
        po_mainActor_ = pa_boulder;
        fallHeight_ = std::dynamic_pointer_cast<Pushable>(po_mainActor_) -> getFallHeight();
    }

    void FallingBoulderEvent::destroy()
    {
        if (ticks_ == 0)
        {
            auto& eventHandler = EventHandler::getInstance();
            Rectangle hitbox = po_mainActor_ -> getHitbox();
            std::vector<std::shared_ptr<Enemy>> enemies = CoreLogic::DataProcessing::ActorStorage::getEnemies();
            for (std::shared_ptr<Enemy> enemy: enemies)
            {
                if (enemy == nullptr)
                {
                    continue;
                }
                if (std::dynamic_pointer_cast<Actor>(enemy)->getElevation() != std::static_pointer_cast<Pushable>(po_mainActor_) -> getNewElevation())
                {
                    continue;
                }
                if (CheckCollisionRecs(hitbox, enemy -> getHitbox()))
                {
                    eventHandler.handleEvents({DISCONNECT}, enemy -> getId());
                }
            }
        }
        if (ticks_ % 5 == 0)
        {
            po_mainActor_ -> shiftFrame(/**@Attention: set to Breaking frames*/);
        }
        if (ticks_ >= 20)
        {
            throw true;
        }
        ticks_++;
    }
} // CoreLogic
// EventManagement