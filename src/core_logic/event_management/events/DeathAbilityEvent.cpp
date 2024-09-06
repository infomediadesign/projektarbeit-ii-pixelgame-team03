//
// Created by keanu on 9/6/2024.
//

#include "DeathAbilityEvent.h"
#include "BellDeathAbilityEvent.h"


namespace CoreLogic::EventManagement
{
    std::unique_ptr<DeathAbilityEvent> DeathAbilityEvent::transform()
    {
        switch (std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_)->getDroneType())
        {
            case Actors::Drone::WORKER:
                throw EventException("Worker no Death Ability", false);
            case Actors::Drone::SCOUT:
                return std::make_unique<BellDeathAbilityEvent>();
        }
    }
} // CoreLogic
// EventManagement