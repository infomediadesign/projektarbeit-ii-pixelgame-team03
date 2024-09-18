//
// Created by keanu on 9/6/2024.
//

#ifndef HIVE_DRONEDISCONNECTEVENT_H
#define HIVE_DRONEDISCONNECTEVENT_H


#include "Event.h"

namespace CoreLogic::EventManagement
{

    class DroneDisconnectEvent: public Event
    {
    public:
        DroneDisconnectEvent();
        void update() override;
        ~DroneDisconnectEvent();
    };

} // CoreLogic
// EventManagement

#endif //HIVE_DRONEDISCONNECTEVENT_H
