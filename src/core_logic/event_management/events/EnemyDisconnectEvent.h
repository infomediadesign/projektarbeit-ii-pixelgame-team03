//
// Created by keanu on 9/6/2024.
//

#ifndef HIVE_ENEMYDISCONNECTEVENT_H
#define HIVE_ENEMYDISCONNECTEVENT_H


#include "Event.h"

namespace CoreLogic::EventManagement
{

    class EnemyDisconnectEvent: public Event
    {
    public:
        EnemyDisconnectEvent(int pa_enemyID);
        EnemyDisconnectEvent() = delete;
        void update() override;
        ~EnemyDisconnectEvent();
    };

} // CoreLogic
// EventManagement

#endif //HIVE_ENEMYDISCONNECTEVENT_H
