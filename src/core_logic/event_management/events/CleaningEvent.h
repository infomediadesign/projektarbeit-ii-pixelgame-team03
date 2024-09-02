//
// Created by keanu on 8/2/2024.
//

#ifndef HIVE_CLEANINGEVENT_H
#define HIVE_CLEANINGEVENT_H

#include <memory>
#include "Event.h"
#include "actors/Drone.h"
#include "AbilityEvent.h"
#include "objects/Rubble.h"

namespace CoreLogic::EventManagement
{
    class CleaningEvent : public AbilityEvent
    {
    public:
        CleaningEvent(std::shared_ptr<CoreLogic::EventManagement::Object::Rubble> pa_rubble);
        ~CleaningEvent() = default;
        void update() override;
    protected:
        /**
         *  @Pseudo_Code: Rubble not yet existing
         */
        std::shared_ptr<CoreLogic::EventManagement::Object::Rubble> po_rubble_;
        bool cleaningDone_ = false;
    };
}

#endif //HIVE_CLEANINGEVENT_H
