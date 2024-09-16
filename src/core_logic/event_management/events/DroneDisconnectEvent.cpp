//
// Created by keanu on 9/6/2024.
//

#include "DroneDisconnectEvent.h"
#include "data_processing/Store.h"
#include "SoundHandler.h"


namespace CoreLogic::EventManagement
{
    DroneDisconnectEvent::DroneDisconnectEvent(): Event(DISCONNECT)
    {
        auto &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
        soundHandler.playSound(SoundHandler::DEATH_DRONE);
        po_mainActor_ = CoreLogic::DataProcessing::ActorStorage::getPlayer();
        try
        {
            std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_)->setDroneState(Actors::Drone::DEATH);
        } catch (EventException &e)
        {
            if (!e.wasSuccessful())
            {
                throw e;
            }
        }
    }

    void DroneDisconnectEvent::update()
    {
        if (ticks_ % 3 == 0)
        {
            std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_) ->shiftFrame(2);
        }
        if (ticks_ >=36)
        {
            throw EventException("Drone disconnected", true);
        }

        ticks_++;
    }

    DroneDisconnectEvent::~DroneDisconnectEvent()
    {
        std::shared_ptr<Actors::Drone> drone = std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_);
        drone -> decreaseCurrentHealth();
        if (drone -> getCurrentHealth() <= 0)
        {
            CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::DEATH);
        } else
        {
            DataProcessing::StateMachine::changeState(DataProcessing::DRONE_SELECTION);
        }
    }
} // CoreLogic
// EventManagement