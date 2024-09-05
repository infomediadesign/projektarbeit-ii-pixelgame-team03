//
// Created by keanu on 9/5/2024.
//

#include "InteractionEvent.h"
#include "Store.h"

namespace CoreLogic::EventManagement
{

   InteractionEvent::InteractionEvent(): Event(CoreLogic::EventManagement::EventEnum::INTERACT)
    {
        po_mainActor_ = std::dynamic_pointer_cast<Actor>(CoreLogic::DataProcessing::ActorStorage::getPlayer());
    }

    InteractionEvent::InteractionEvent(CoreLogic::EventManagement::EventEnum pa_ID) :
            Event(pa_ID)
    {
        po_mainActor_ = std::dynamic_pointer_cast<Actor>(CoreLogic::DataProcessing::ActorStorage::getPlayer());
    }

    void InteractionEvent::update(){}

    std::unique_ptr<InteractionEvent> InteractionEvent::transform() const
    {

    }
};