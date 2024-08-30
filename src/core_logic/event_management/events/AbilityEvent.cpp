//
// Created by keanu on 8/2/2024.
//

#include "AbilityEvent.h"
#include "Store.h"


namespace CoreLogic::EventManagement
{
    AbilityEvent::AbilityEvent(): Event(ABILITY)
    {
        po_mainActor_ = std::dynamic_pointer_cast<Actor>(CoreLogic::DataProcessing::ActorStorage::getPlayer());
    }

    std::unique_ptr<AbilityEvent> AbilityEvent::transform()
    {

        return std::unique_ptr<AbilityEvent>();
    }

    AbilityEvent::AbilityEvent(EventEnum pa_ID) : Event(pa_ID)
    {
        po_mainActor_ = std::dynamic_pointer_cast<Actor>(CoreLogic::DataProcessing::ActorStorage::getPlayer());
    }
} // CoreLogic
// EventManagement