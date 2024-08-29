//
// Created by keanu on 8/29/2024.
//

#ifndef HIVE_PUSHEVENT_H
#define HIVE_PUSHEVENT_H


#include <memory>
#include "AbilityEvent.h"

namespace CoreLogic::EventManagement
{

    class PushEvent : public AbilityEvent
    {
    public:
        PushEvent(std::shared_ptr<Pushable> pa_pushable);
        ~PushEvent();
        void update();
    protected:
        std::shared_ptr<Pushable> po_pushable_;
        bool reachedDestination_ = false;
    };

} // CoreLogic
// EventManagement

#endif //HIVE_PUSHEVENT_H
