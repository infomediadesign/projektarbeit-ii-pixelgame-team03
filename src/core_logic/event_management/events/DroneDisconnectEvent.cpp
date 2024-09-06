//
// Created by keanu on 9/6/2024.
//

#include "DroneDisconnectEvent.h"
#include "Store.h"


namespace CoreLogic::EventManagement
{
    DroneDisconnectEvent::DroneDisconnectEvent(): Event(DISCONNECT)
    {
        po_mainActor_ = CoreLogic::DataProcessing::ActorStorage::getPlayer();
        std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_) -> setState(Actors::Drone::DroneState::DISCONNECTED);
    }

    void DroneDisconnectEvent::update()
    {
        if (ticks_ % 3 == 0)
        {
            std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_) ->shiftFrame(/**@warning: to determine frame shifts*/);
        }
        if (ticks_ >=36)
        {
            throw EventException("Drone disconnected", true);
        }

        ticks_++;
    }

    DroneDisconnectEvent::~DroneDisconnectEvent()
    {
        std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_) -> decreaseCurrentHealth();
        DataProcessing::StateMachine::changeState(DataProcessing::DRONE_SELECTION);
    }
} // CoreLogic
// EventManagement