//
// Created by keanu on 9/5/2024.
//

#ifndef HIVE_CHECKPOINTEVENT_H
#define HIVE_CHECKPOINTEVENT_H


#include "InteractionEvent.h"
#include "actors/objects/DroneRespawnPoint.h"

namespace CoreLogic::EventManagement
{

    class CheckpointEvent : InteractionEvent
    {
    public:
        CheckpointEvent(std::shared_ptr<Object::DroneRespawnPoint> pa_checkpoint);
    };

} // CoreLogic
// EventManagement

#endif //HIVE_CHECKPOINTEVENT_H
