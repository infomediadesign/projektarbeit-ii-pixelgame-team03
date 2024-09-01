//
// Created by keanu on 8/2/2024.
//

#include "AbilityEvent.h"
#include "Store.h"
#include "CleaningEvent.h"
#include "PushEvent.h"
#include "JumpEvent.h"
#include "PushBarrelEvent.h"


namespace CoreLogic::EventManagement
{
    AbilityEvent::AbilityEvent(): Event(ABILITY)
    {
        po_mainActor_ = std::dynamic_pointer_cast<Actor>(CoreLogic::DataProcessing::ActorStorage::getPlayer());
    }

    std::unique_ptr<AbilityEvent> AbilityEvent::transform()
    {
        /**
         * @Pseudo_Code: enum AbilityType not yet existing
         * @todo: Code enum AbilityType and Ability Type into Ability Object Class
         */
        Ability ability = std::dynamic_pointer_cast<Drone>(po_mainActor_) -> getAbility();
        AbilityType abilityType = ability -> getAbilityType();

        AbilityEvent transformEvent;

        switch (abilityType)
        {
            case AbilityType::CLEANING:
                return std::make_unique<CleaningEvent>(ability);
            case AbilityType::PUSH:
                return std::make_unique<PushEvent>(ability);
            case AbilityType::Barrel:
                return std::make_unique<PushBarrelEvent>(ability);
            case AbilityType::JUMP:
                std::unique_ptr<JumpEvent> jump = std::make_unique<JumpEvent>(ability);
                throw EventException("Jump Event Executed");
        }
    }

    AbilityEvent::AbilityEvent(EventEnum pa_ID) : Event(pa_ID)
    {
        po_mainActor_ = std::dynamic_pointer_cast<Actor>(CoreLogic::DataProcessing::ActorStorage::getPlayer());
    }

    void AbilityEvent::update(){}
} // CoreLogic
// EventManagement