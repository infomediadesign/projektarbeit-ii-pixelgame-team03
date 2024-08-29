//
// Created by keanu on 8/2/2024.
//

#ifndef HIVE_CLEANINGEVENT_H
#define HIVE_CLEANINGEVENT_H

#include <memory>
#include "Event.h"
#include "actors/Drone.h"
#include "AbilityEvent.h"

namespace CoreLogic::EventManagement
{
    class CleaningEvent : public AbilityEvent
    {
    public:
        CleaningEvent(std::shared_ptr<Rubble> pa_rubble);
        ~CleaningEvent() = default;
        void update();
    protected:
        /**
         *  @Pseudo_Code: Rubble not yet existing
         */
        std::shared_ptr<Rubble> po_rubble_;
        bool cleaningDone_ = false;
    };
}

#endif //HIVE_CLEANINGEVENT_H
