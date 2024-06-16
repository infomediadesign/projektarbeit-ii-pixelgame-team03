//
// Created by keanu on 6/9/2024.
//

#ifndef HIVE_EVENTHANDLER_H
#define HIVE_EVENTHANDLER_H


#include <map>
#include <vector>
#include <memory>
#include "event_management/events/Event.h"
#include "event_management/events/MovementEvent.h"


class EventHandler
{
public:
    EventHandler();
    ~EventHandler();

    void handleEvents(EventEnum events[]);
    void update();

private:
    std::unique_ptr<std::vector<Event>> activeEvents_;
    int activeEventIDs_;
    int deactivateEventIDs_;
    bool movementBlocked_ = false;
    std::unique_ptr<MovementEvent> po_movementEvent_;

    void activateEvent(EventEnum pa_ActivateEvent);
    void deactivateEvent(EventEnum pa_DeactivateEvent);




};


#endif //HIVE_EVENTHANDLER_H
