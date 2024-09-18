//
// Created by keanu on 9/5/2024.
//

#include "ClimbingEvent.h"
#include "data_processing/Store.h"


namespace CoreLogic::EventManagement
{
    ClimbingEvent::ClimbingEvent(std::shared_ptr<Object::Vine> pa_vine) : InteractionEvent(CLIMB)
    {
        Vector2 destination = pa_vine->getCoordinates();
        int elevationChange = pa_vine->getNewElevation();
        po_mainActor_ = CoreLogic::DataProcessing::ActorStorage::getPlayer();
        std::vector<std::shared_ptr<Actor>> barriers = CoreLogic::DataProcessing::ActorStorage::getCollidables()->at(elevationChange);
        if (!barriers.empty())
        {
            for (auto &barrier: barriers)
            {
                if (barrier == nullptr)
                {
                    continue;
                }
                if (barrier->getElevation() != elevationChange)
                {
                    continue;
                }
                if (barrier->getCollisionType() == Actor::CollisionType::NONE)
                {
                    continue;
                }
                Rectangle barrierHitbox = barrier->getHitbox();
                Rectangle playerHB = po_mainActor_->getHitbox();
                Rectangle destinationHB = {destination.x, destination.y, playerHB.width, playerHB.height};
                if (CheckCollisionRecs(barrierHitbox, destinationHB))
                {
                    throw EventException("Climbing Event Failed", false);
                }
            }
        }

        std::dynamic_pointer_cast<CoreLogic::EventManagement::Actors::MovableActor>(po_mainActor_) -> setPosition(destination);
        std::dynamic_pointer_cast<CoreLogic::EventManagement::Actors::MovableActor>(po_mainActor_) -> setElevation(elevationChange);
        throw EventException("Climbing Event Executed", true);
    }
} // CoreLogic
// EventManagement