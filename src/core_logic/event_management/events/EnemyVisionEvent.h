//
// Created by keanu on 9/6/2024.
//

#ifndef HIVE_ENEMYVISIONEVENT_H
#define HIVE_ENEMYVISIONEVENT_H


#include "Event.h"

namespace CoreLogic::EventManagement
{

    class EnemyVisionEvent: public Event
    {
    public:
        explicit EnemyVisionEvent(int pa_id);
        void update() override;
    };

} // CoreLogic
// EventManagement

#endif //HIVE_ENEMYVISIONEVENT_H
