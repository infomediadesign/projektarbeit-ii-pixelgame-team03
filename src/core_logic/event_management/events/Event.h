//
// Created by keanu on 6/10/2024.
//

#ifndef HIVE_EVENT_H
#define HIVE_EVENT_H

#include <memory>
#include "event_management/Actor.h"
#include "event_management/InputHandler.h"


namespace CoreLogic::EventManagement
{
    class Event
    {

    public:
        explicit Event(EventEnum pa_ID);
        virtual ~Event() = default;
        virtual void update() = 0;
        EventEnum getID();
    protected:
        /**
         *@question: needed?
         **/
        std::shared_ptr<Actor> po_mainActor_;

        Event() = delete;

        const EventEnum id_;

        /**
         *@todo: static input Handler?
         **/

    };
}


#endif //HIVE_EVENT_H
