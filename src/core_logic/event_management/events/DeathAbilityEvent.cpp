//
// Created by keanu on 9/6/2024.
//

#include "DeathAbilityEvent.h"
#include "BellDeathAbilityEvent.h"


namespace CoreLogic::EventManagement
{
    std::unique_ptr<DeathAbilityEvent> DeathAbilityEvent::transform() const
    {
        switch (std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_)->getDroneType())
        {
            case Actors::Drone::WORKER:
                throw EventException("Worker no Death Ability", false);
            case Actors::Drone::SCOUT:
                return std::make_unique<BellDeathAbilityEvent>();
        }
    }

    DeathAbilityEvent::DeathAbilityEvent(): Event(DEATH_ABILITY)
    {
        po_mainActor_ = CoreLogic::DataProcessing::ActorStorage::getPlayer();
        if (std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_)-> getDroneType() == Actors::Drone::WORKER)
        {
            throw EventException("Worker no Death Ability", false);
        }
        try
        {
            std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_) -> setDroneState(Actors::Drone::DEATH_ABILITY);
        } catch (EventException &e)
        {
            if (!e.wasSuccessful())
            {
                throw e;
            }
        }
    }

} // CoreLogic
// EventManagement