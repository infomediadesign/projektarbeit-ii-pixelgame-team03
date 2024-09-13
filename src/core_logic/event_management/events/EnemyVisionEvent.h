//
// Created by keanu on 9/6/2024.
//

#ifndef HIVE_ENEMYVISIONEVENT_H
#define HIVE_ENEMYVISIONEVENT_H


#include "Event.h"
#include "actors/Drone.h"

namespace CoreLogic::EventManagement
{

    class EnemyVisionEvent: public Event
    {
    public:
        explicit EnemyVisionEvent(int pa_id);
        ~EnemyVisionEvent();
        void update() override;
    protected:
        bool found_ = false;

        std::shared_ptr<Actors::Drone> po_player_;

        void lookout();
        void shoot();
    };

} // CoreLogic
// EventManagement

#endif //HIVE_ENEMYVISIONEVENT_H
