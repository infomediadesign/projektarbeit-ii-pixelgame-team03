//
// Created by keanu on 9/6/2024.
//

#ifndef HIVE_DEATHABILITYEVENT_H
#define HIVE_DEATHABILITYEVENT_H


#include "Event.h"
#include "Store.h"

namespace CoreLogic::EventManagement
{

    class DeathAbilityEvent: public Event
    {
    public:
        DeathAbilityEvent(): Event(DEATH_ABILITY)
        {
            po_mainActor_ = CoreLogic::DataProcessing::ActorStorage::getPlayer();
        };
        std::unique_ptr<DeathAbilityEvent> transform();

    };

} // CoreLogic
// EventManagement

#endif //HIVE_DEATHABILITYEVENT_H
