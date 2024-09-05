//
// Created by keanu on 9/5/2024.
//

#ifndef HIVE_INTERACTIONEVENT_H
#define HIVE_INTERACTIONEVENT_H


#include <memory>
#include "Event.h"

namespace CoreLogic::EventManagement
{
    class InteractionEvent : public Event
    {
    public:
        InteractionEvent();

        explicit InteractionEvent(EventEnum pa_ID);
        void update() override;
        virtual std::unique_ptr<InteractionEvent> transform() const;
    };
}


#endif //HIVE_INTERACTIONEVENT_H
