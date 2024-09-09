//
// Created by keanu on 9/1/2024.
//

#ifndef HIVE_PUSHBARRELEVENT_H
#define HIVE_PUSHBARRELEVENT_H


#include "AbilityEvent.h"
#include "actors/objects/Barrel.h"

namespace CoreLogic::EventManagement
{

    class PushBarrelEvent: public AbilityEvent
    {
    public:
        PushBarrelEvent(std::shared_ptr<Object::Barrel> pa_barrel);
        ~PushBarrelEvent();
        void update() override;
    protected:
        std::shared_ptr<Object::Barrel> po_barrel_;
        bool reachedDestination_ = false;
        Vector2 push_;
    };

} // CoreLogic
// EventManagement

#endif //HIVE_PUSHBARRELEVENT_H
