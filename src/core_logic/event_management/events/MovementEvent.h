//
// Created by keanu on 6/10/2024.
//

#ifndef HIVE_MOVEMENTEVENT_H
#define HIVE_MOVEMENTEVENT_H


#include "Event.h"
#include "event_management/EventUtilities.h"

namespace CoreLogic::EventManagement
{
    class MovementEvent: public Event
    {
    public:
        MovementEvent();
        void update() override;
        void startMove(EventEnum pa_Event);
        void updateMainActor();
    protected:
        void checkStillPressed();
        void updateActorDir();
        void stop();
        bool ticksRunning_ = false;
        EventEnum primaryDir_;
        std::map<EventEnum, bool> directionMap_;
        InputHandler inputHandler_;
    };
}


#endif //HIVE_MOVEMENTEVENT_H
