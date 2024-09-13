//
// Created by keanu on 9/1/2024.
//

#ifndef HIVE_FALLINGBOULDEREVENT_H
#define HIVE_FALLINGBOULDEREVENT_H


#include "FallingEvent.h"
#include "actors/objects/Boulder.h"

namespace CoreLogic::EventManagement
{

    class FallingBoulderEvent: public FallingEvent
    {

    public:
        FallingBoulderEvent(std::shared_ptr<Object::Boulder> pa_boulder);
    protected:
        void destroy() override;
        void fall() override;
    };

} // CoreLogic
// EventManagement

#endif //HIVE_FALLINGBOULDEREVENT_H
