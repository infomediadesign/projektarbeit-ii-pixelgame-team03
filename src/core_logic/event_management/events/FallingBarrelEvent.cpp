//
// Created by keanu on 9/1/2024.
//

#include "FallingBarrelEvent.h"
#include "EventHandler.h"
#include "data_processing/Store.h"
#include "actors/Enemy.h"
#include "actors/objects/Uplink.h"


namespace CoreLogic::EventManagement
{
    FallingBarrelEvent::FallingBarrelEvent(std::shared_ptr<Object::Barrel> pa_barrel) : FallingEvent(BARREL_FALL)
    {
        po_mainActor_ = pa_barrel;
        fallHeight_ = std::dynamic_pointer_cast<Object::Barrel>(po_mainActor_)
                ->getFallHeight();
    }


    void FallingBarrelEvent::destroy()
    {
        if (ticks_ == 0)
        {

            auto& eventHandler = EventHandler::getInstance();
            Rectangle explosionRadius;
            int tileSize = CoreLogic::DataProcessing::global_tileSize;
            explosionRadius.x = po_mainActor_ -> getPosition().x - (tileSize * 2);
            explosionRadius.y = po_mainActor_ -> getPosition().y - (tileSize * 2);
            explosionRadius.width = po_mainActor_ -> getSize().x + (tileSize * 5);
            explosionRadius.height = po_mainActor_ -> getSize().y + (tileSize * 5);
            std::vector<std::shared_ptr<Actors::Enemy>> &enemies = (CoreLogic::DataProcessing::ActorStorage::getEnemies())->at(std::dynamic_pointer_cast<Object::Barrel>(po_mainActor_)->getNewElevation());
            for (auto &enemy: enemies)
            {
                if (enemy == nullptr|| enemy -> getDead())
                {
                    continue;
                }
                if (std::dynamic_pointer_cast<Actor>(enemy)->getElevation() !=
                std::static_pointer_cast<Object::Barrel>(po_mainActor_) -> getNewElevation())
                {
                    continue;
                }
                if (CheckCollisionRecs(explosionRadius, enemy -> getHitbox()))
                {
                    eventHandler.handleEvents({ENEMY_DEATH}, enemy -> getId());
                }
            }
        }
        if (ticks_ % 5 == 0)
        {
            po_mainActor_ -> shiftFrame(1);
        }
        if (ticks_ == 40)
        {
            std::vector<std::shared_ptr<Object::Uplink>> &uplinks = CoreLogic::DataProcessing::ActorStorage::getUplinks()->at(std::dynamic_pointer_cast<Object::Barrel>(po_mainActor_)->getNewElevation());
            for (auto &uplink: uplinks)
            {
                if (uplink == nullptr)
                {
                    continue;
                }
                if (std::dynamic_pointer_cast<Actor>(uplink)->getElevation() != std::static_pointer_cast<Object::Boulder>
                        (po_mainActor_) -> getNewElevation())
                {
                    continue;
                }
                if (CheckCollisionRecs(uplink -> getHitbox(), po_mainActor_ -> getHitbox()))
                {
                    DataProcessing::StateMachine::changeState(DataProcessing::END_SCENE);
                }
            }
        }
        if (ticks_ >= 60)
        {
            throw EventException("Falling Event Executed", true);
        }
        ticks_++;
    }
} // CoreLogic
// EventManagement