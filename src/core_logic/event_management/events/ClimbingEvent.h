//
// Created by keanu on 9/5/2024.
//

#ifndef HIVE_CLIMBINGEVENT_H
#define HIVE_CLIMBINGEVENT_H


#include "InteractionEvent.h"
#include "actors/objects/Vine.h"

namespace CoreLogic::EventManagement
{

    class ClimbingEvent : public InteractionEvent
    {
    public:
        ClimbingEvent(std::shared_ptr<Object::Vine> pa_vine);
    };

} // CoreLogic
// EventManagement

#endif //HIVE_CLIMBINGEVENT_H
