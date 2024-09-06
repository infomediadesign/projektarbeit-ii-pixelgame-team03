//
// Created by keanu on 9/6/2024.
//

#ifndef HIVE_BELLDEATHABILITYEVENT_H
#define HIVE_BELLDEATHABILITYEVENT_H


#include "DeathAbilityEvent.h"

namespace CoreLogic::EventManagement
{

    class BellDeathAbilityEvent: public DeathAbilityEvent
    {
    public:
        BellDeathAbilityEvent();
        void update() override;
        ~BellDeathAbilityEvent();
    };

} // CoreLogic
// EventManagement

#endif //HIVE_BELLDEATHABILITYEVENT_H
