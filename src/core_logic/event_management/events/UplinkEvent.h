//
// Created by keanu on 9/5/2024.
//

#ifndef HIVE_UPLINKEVENT_H
#define HIVE_UPLINKEVENT_H


#include "InteractionEvent.h"
#include "actors/objects/Uplink.h"

namespace CoreLogic::EventManagement
{

    class UplinkEvent : InteractionEvent
    {
    public:
        UplinkEvent(std::shared_ptr<Object::Uplink> pa_uplink): InteractionEvent() {};
        ~UplinkEvent() = default;
        void update() override;
    };

} // CoreLogic
// EventManagement

#endif //HIVE_UPLINKEVENT_H
