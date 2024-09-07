//
// Created by keanu on 9/6/2024.
//

#ifndef HIVE_DEATHABILITYEVENT_H
#define HIVE_DEATHABILITYEVENT_H


#include "Event.h"
#include "data_processing/Store.h"

namespace CoreLogic::EventManagement
{

    class DeathAbilityEvent: public Event
    {
    public:
        DeathAbilityEvent();
        virtual std::unique_ptr<DeathAbilityEvent> transform() const;
        void update() override{};

    };

} // CoreLogic
// EventManagement

#endif //HIVE_DEATHABILITYEVENT_H
