//
// Created by keanu on 8/30/2024.
//

#ifndef HIVE_FALLINGEVENT_H
#define HIVE_FALLINGEVENT_H

#include "Event.h"

namespace CoreLogic::EventManagement
{
    class FallingEvent : public Event
    {

    public:
        FallingEvent(int pa_actorID);
        ~FallingEvent();
        FallingEvent(): Event(EventEnum::FALLING){};
        void update() override;
        virtual std::unique_ptr<FallingEvent> transform();
    protected:
        int fallHeight_;
        float fallenHeight_ = 0.0f;
        bool broken_ = false;
        void fall();
        virtual void destroy(){};
        bool barrel_;/*
        void explode();*/
        void crumble();
    };

}

#endif //HIVE_FALLINGEVENT_H
