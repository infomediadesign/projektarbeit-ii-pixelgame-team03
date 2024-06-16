//
// Created by keanu on 6/10/2024.
//

#ifndef HIVE_EVENT_H
#define HIVE_EVENT_H

#include <memory>
#include "event_management/Actor.h"


class Event
{

public:
    Event() = default;
    virtual ~Event() = default;
    virtual void update() = 0;
protected:
    std::shared_ptr<CoreLogic::EventManagement::Actor> po_mainActor_;
};


#endif //HIVE_EVENT_H
