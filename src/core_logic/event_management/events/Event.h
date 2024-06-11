//
// Created by keanu on 6/10/2024.
//

#ifndef HIVE_EVENT_H
#define HIVE_EVENT_H

#include <memory>
#include "event_management/Actor.h"

enum EventEnum
{
    MOVEUP_EVENT = 0x00001,
    MOVEDOWN_EVENT = 0x00002,
    MOVELEFT_EVENT = 0x00004,
    MOVERIGHT_EVENT = 0x00008,
    PAUSE_EVENT = 0x00010,
    EXIT_EVENT = 0x00020,
    UNDEFINED_EVENT = 0x00040
};

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
