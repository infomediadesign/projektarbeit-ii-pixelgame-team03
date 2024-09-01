//
// Created by keanu on 9/1/2024.
//

#include "FallingBarrelEvent.h"
#include "EventHandler.h"
#include "Store.h"


namespace CoreLogic::EventManagement
{
    FallingBarrelEvent::FallingBarrelEvent(std::shared_ptr<Barrel> pa_barrel) : FallingEvent()
    {
        po_mainActor_ = pa_barrel;
        fallHeight_ = std::dynamic_pointer_cast<Barrel>(po_mainActor_)->getFallHeight();
    }


    void FallingBarrelEvent::destroy()
    {
        if (ticks_ == 0)
        {
            /**
             * @todo: Code Drawing for different frame sizes
             */

            auto& eventHandler = EventHandler::getInstance();
            Rectangle explosionRadius;
            int tileSize = CoreLogic::DataProcessing::tileSize;
            explosionRadius.x = po_mainActor_ -> getPosition().x - (tileSize * 2);
            explosionRadius.y = po_mainActor_ -> getPosition().y - (tileSize * 2);
            explosionRadius.width = po_mainActor_ -> getSize().x + (tileSize * 5);
            explosionRadius.height = po_mainActor_ -> getSize().y + (tileSize * 5);
            std::vector<std::shared_ptr<Enemy>> enemies = CoreLogic::DataProcessing::ActorStorage::getEnemies();
            for (std::shared_ptr<Enemy> enemy: enemies)
            {
                if (enemy == nullptr)
                {
                    continue;
                }
                if (std::dynamic_pointer_cast<Actor>(enemy)->getElevation() != std::static_pointer_cast<Barrel>(po_mainActor_) -> getNewElevation())
                {
                    continue;
                }
                if (CheckCollisionRecs(explosionRadius, enemy -> getHitbox()))
                {
                    eventHandler.handleEvents({DISCONNECT}, enemy -> getId());
                }
            }
        }
        if (ticks_ % 5 == 0)
        {
            po_mainActor_ -> shiftFrame(/**@Attention: set to Breaking frames*/);
        }
        if (ticks_ >= 60)
        {
            throw true;
        }
        ticks_++;
    }
} // CoreLogic
// EventManagement