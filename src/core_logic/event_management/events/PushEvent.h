//
// Created by keanu on 8/29/2024.
//

#ifndef HIVE_PUSHEVENT_H
#define HIVE_PUSHEVENT_H


#include <memory>
#include "AbilityEvent.h"
#include "actors/objects/Boulder.h"

namespace CoreLogic::EventManagement
{

    class PushEvent : public AbilityEvent
    {
    public:
        PushEvent(std::shared_ptr<Object::Boulder> pa_pushable);
        ~PushEvent();
        void update() override;
    protected:
        std::shared_ptr<Object::Boulder> po_pushable_;
        bool reachedDestination_ = false;
        bool extended_ = false;
        Vector2 push_;
        int frameCount_=0;

    };

} // CoreLogic
// EventManagement

#endif //HIVE_PUSHEVENT_H
