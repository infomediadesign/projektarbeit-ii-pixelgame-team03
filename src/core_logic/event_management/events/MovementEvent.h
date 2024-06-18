//
// Created by keanu on 6/10/2024.
//

#ifndef HIVE_MOVEMENTEVENT_H
#define HIVE_MOVEMENTEVENT_H


#include "Event.h"
#include "event_management/EventUtilities.h"
#include "EventUtilities.h"

namespace CoreLogic::EventManagement
{
    class MovementEvent: public Event
    {
    public:
        MovementEvent();
        void update() override;
        void startMove(EventEnum pa_Event);
    private:
        void checkStillPressed();
        void updateAxis();
        int ticks_ = 0;
        bool ticksRunning_ = false;
        EventEnum primaryDir_;
        std::map<EventEnum, bool> directionMap_;
    };
}


#endif //HIVE_MOVEMENTEVENT_H
