//
// Created by keanu on 6/9/2024.
//

#ifndef HIVE_EVENTHANDLER_H
#define HIVE_EVENTHANDLER_H


#include <map>
#include <vector>
#include <memory>
#include <mutex>
#include "event_management/events/Event.h"
#include "event_management/events/MovementEvent.h"
#include "EventUtilities.h"


namespace CoreLogic::EventManagement
{
    class EventHandler
    {
    public:
        static EventHandler &getInstance();
        ~EventHandler();
        void handleEvents(const std::vector<EventEnum> &pa_Events, int pa_actorID);
        void switchLevels();

        void update();
    private:
        EventHandler();
        /**
         * @todo: rework: std::map<int, std::vector<Event>> activeEvents_;
         * @todo: reworc activeEventIDs_ as soon as feedback is here
         **/
        std::map<int, std::vector<std::unique_ptr<Event>>> po_activeEvents_;

//      std::unique_ptr<std::map<int, EventEnum>> activeEventIDs_;

        int deactivateEventIDs_;
        bool movementBlocked_ = false;
        std::unique_ptr<MovementEvent> po_movementEvent_;

        void activateEvent(EventEnum pa_activateEvent);
        void deactivateEvent(EventEnum pa_deactivateEvent);

        static std::mutex eventHandler_mutex_;


    };
}


#endif //HIVE_EVENTHANDLER_H
