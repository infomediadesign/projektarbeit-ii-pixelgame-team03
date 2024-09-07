//
// Created by keanu on 9/5/2024.
//

#include "CheckpointEvent.h"
#include "data_processing/Store.h"


namespace CoreLogic::EventManagement
{
    CheckpointEvent::CheckpointEvent(std::shared_ptr<Object::DroneRespawnPoint> pa_checkpoint): InteractionEvent(CHECKPOINT)
    {
        auto activeSpawnPoint = CoreLogic::DataProcessing::ActorStorage::getActiveSpawnPoint();
        if (activeSpawnPoint == nullptr)
        {
            throw EventException("No active spawn point", false);
        }
        if (pa_checkpoint->getRespawnState() == Object::DroneRespawnPoint::UNDISCOVERED || pa_checkpoint->getRespawnState() == Object::DroneRespawnPoint::DISCOVERED)
        {
            pa_checkpoint->changeState(Object::DroneRespawnPoint::ACTIVATED);
            activeSpawnPoint->changeState(Object::DroneRespawnPoint::DISCOVERED);
            activeSpawnPoint = pa_checkpoint;
            CoreLogic::DataProcessing::StateMachine::changeState(DataProcessing::DRONE_SELECTION);
            throw EventException("Checkpoint Event Executed", true);
        } else if (pa_checkpoint->getRespawnState() == Object::DroneRespawnPoint::ACTIVATED) {
            if (pa_checkpoint != activeSpawnPoint)
            {
                throw EventException("Active spawn point does not match checkpoint", false);
            }
            CoreLogic::DataProcessing::StateMachine::changeState(DataProcessing::DRONE_SELECTION);
            throw EventException("Checkpoint Event Executed", true);
        } else {
            throw EventException("Invalid checkpoint state", false);
        }
    }
} // CoreLogic
// EventManagement