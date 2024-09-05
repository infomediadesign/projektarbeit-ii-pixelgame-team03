//
// Created by keanu on 9/5/2024.
//

#include "CheckpointEvent.h"
#include "Store.h"


namespace CoreLogic::EventManagement
{
    CheckpointEvent::CheckpointEvent(std::shared_ptr<Object::DroneRespawnPoint> pa_checkpoint): InteractionEvent(CHECKPOINT)
    {
        auto activeSpawnPoint = CoreLogic::DataProcessing::ActorStorage::getActiveSpawnPoint();
        if (activeSpawnPoint == nullptr)
        {
            throw std::runtime_error("No active spawn point");
        }
        if (pa_checkpoint->getRespawnState() == Object::DroneRespawnPoint::UNDISCOVERED || pa_checkpoint->getRespawnState() == Object::DroneRespawnPoint::DISCOVERED)
        {
            pa_checkpoint->changeState(Object::DroneRespawnPoint::ACTIVATED);
            activeSpawnPoint->changeState(Object::DroneRespawnPoint::DISCOVERED);
            activeSpawnPoint = pa_checkpoint;
            CoreLogic::DataProcessing::setGameState(DRONE_SWITCH);
            throw EventException("Checkpoint Event Executed");
        } else if (pa_checkpoint->getRespawnState() == Object::DroneRespawnPoint::ACTIVATED) {
            if (pa_checkpoint != activeSpawnPoint)
            {
                throw std::runtime_error("Active spawn point does not match checkpoint");
            }
            CoreLogic::DataProcessing::setGameState(DRONE_SWITCH);
            throw EventException("Checkpoint Event Executed");
        } else {
            throw std::runtime_error("Invalid checkpoint state");
        }
    }
} // CoreLogic
// EventManagement