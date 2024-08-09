//
// Created by keanu on 8/2/2024.
//

#include "AbilityEvent.h"


namespace CoreLogic::EventManagement
{
    AbilityEvent::AbilityEvent(): Event(ABILITY)
    {

    }

    std::unique_ptr<AbilityEvent> AbilityEvent::transform()
    {

        return std::unique_ptr<AbilityEvent>();
    }
} // CoreLogic
// EventManagement