//
// Created by keanu on 8/31/2024.
//

#ifndef HIVE_JUMPEVENT_H
#define HIVE_JUMPEVENT_H

#include "AbilityEvent.h"
#include "actors/objects/JumpPoint.h"

namespace CoreLogic::EventManagement
{

    class JumpEvent : public AbilityEvent
    {
    public:
        explicit JumpEvent(std::shared_ptr<Object::JumpPoint> pa_jumpPoint);
        ~JumpEvent();
    };
}

#endif //HIVE_JUMPEVENT_H
