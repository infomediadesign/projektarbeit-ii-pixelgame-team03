//
// Created by keanu on 8/2/2024.
//

#include "AbilityEvent.h"
#include "Store.h"
#include "CleaningEvent.h"
#include "PushEvent.h"
#include "JumpEvent.h"
#include "PushBarrelEvent.h"
#include "objects/Boulder.h"


namespace CoreLogic::EventManagement
{
    enum class AbilityType
    {
        CLEANING,
        PUSH,
        JUMP,
        BARREL
    };
    AbilityEvent::AbilityEvent(): Event(ABILITY)
    {
        po_mainActor_ = std::dynamic_pointer_cast<Actor>(CoreLogic::DataProcessing::ActorStorage::getPlayer());
    }

    std::unique_ptr<AbilityEvent> AbilityEvent::transform() const
    {
        /**
         * @Pseudo_Code: enum AbilityType not yet existing
         * @todo: Code enum AbilityType and Ability Type into Ability Object Class
         */
        std::shared_ptr <CoreLogic::EventManagement::Object::Ability> ability = std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_) -> getAbility();
        Object::Ability::AbilityType abilityType = ability -> getAbilityType();

        AbilityEvent transformEvent;

        switch (abilityType)
        {
            case Object::Ability::AbilityType::CLEANING:
                return std::make_unique<CleaningEvent>(std::dynamic_pointer_cast<Object::Rubble>(ability));
            case Object::Ability::AbilityType::PUSH:
                return std::make_unique<PushEvent>(std::dynamic_pointer_cast<Object::Boulder>(ability));
            case Object::Ability::AbilityType::BARREL:
                return std::make_unique<PushBarrelEvent>(std::dynamic_pointer_cast<Object::Barrel>(ability));
            case Object::Ability::AbilityType::JUMP:
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