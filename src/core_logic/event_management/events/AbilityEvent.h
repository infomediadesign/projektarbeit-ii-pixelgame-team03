//
// Created by keanu on 8/2/2024.
//

#ifndef HIVE_ABILITYEVENT_H
#define HIVE_ABILITYEVENT_H


#include "Event.h"

namespace CoreLogic::EventManagement
{

    class AbilityEvent: public Event
    {
    public:
        AbilityEvent();

        AbilityEvent(EventEnum pa_ID);
        std::unique_ptr<AbilityEvent> transform();
    };

} // CoreLogic
// EventManagement

#endif //HIVE_ABILITYEVENT_H