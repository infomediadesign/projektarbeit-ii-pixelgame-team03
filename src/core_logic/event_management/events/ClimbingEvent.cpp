//
// Created by keanu on 9/5/2024.
//

#include "ClimbingEvent.h"
#include "Store.h"


namespace CoreLogic::EventManagement
{
    ClimbingEvent::ClimbingEvent(std::shared_ptr<Object::Vine> pa_vine) : InteractionEvent(CLIMB)
    {
        Vector2 destination = pa_vine->getCoordinates();
        int elevationChange = pa_vine->getElevationChange();
        po_mainActor_ = CoreLogic::DataProcessing::ActorStorage::getPlayer();
        std::dynamic_pointer_cast<CoreLogic::EventManagement::Actors::MovableActor>(po_mainActor_) -> setPosition(destination);
        std::dynamic_pointer_cast<CoreLogic::EventManagement::Actors::MovableActor>(po_mainActor_) -> setElevation(elevationChange);
        throw EventException("Climbing Event Executed");
    }
} // CoreLogic
// EventManagement