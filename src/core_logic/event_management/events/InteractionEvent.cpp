//
// Created by keanu on 9/5/2024.
//

#include "InteractionEvent.h"
#include "Store.h"
#include "ClimbingEvent.h"
#include "NoteEvent.h"
#include "CheckpointEvent.h"
#include "UplinkEvent.h"
#include "actors/objects/Uplink.h"
#include "actors/objects/DroneRespawnPoint.h"
#include "actors/objects/Vine.h"
#include "actors/objects/Note.h"
#include "actors/objects/Interaction.h"


namespace CoreLogic::EventManagement
{

   InteractionEvent::InteractionEvent(): Event(CoreLogic::EventManagement::EventEnum::INTERACT)
    {
        po_mainActor_ = std::dynamic_pointer_cast<Actor>(CoreLogic::DataProcessing::ActorStorage::getPlayer());
        try
        {
            std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_) -> setDroneState(Actors::Drone::INTERACTING);
        } catch (EventException &e) {
            if (!e.wasSuccessful())
            {
                throw e;
            }
        }
    }

    InteractionEvent::InteractionEvent(CoreLogic::EventManagement::EventEnum pa_ID) :
            Event(INTERACT)
    {
        po_mainActor_ = std::dynamic_pointer_cast<Actor>(CoreLogic::DataProcessing::ActorStorage::getPlayer());
        variantId_ = pa_ID;
    }

    void InteractionEvent::update(){}

    std::unique_ptr<InteractionEvent> InteractionEvent::transform() const
    {
        /**
        * @Pseudo_Code: enum AbilityType not yet existing
        * @todo: Code enum AbilityType and Ability Type into Ability Object Class
        */
        std::shared_ptr<Object::Interaction> interaction = std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_)->getInteraction();
        Object::Interaction::InteractionType interactionType = interaction->getType();

        InteractionEvent transformEvent;

        switch (interactionType)
        {
            case Object::Interaction::InteractionType::CLIMBING:
                return std::make_unique<ClimbingEvent>(std::dynamic_pointer_cast<Object::Vine>(interaction));
            case Object::Interaction::InteractionType::NOTE:
                return std::make_unique<NoteEvent>(std::dynamic_pointer_cast<Object::Note>(interaction));
            case Object::Interaction::InteractionType::CHECKPOINT:
                return std::make_unique<CheckpointEvent>(std::dynamic_pointer_cast<Object::DroneRespawnPoint>(interaction));

            case Object::Interaction::InteractionType::UPLINK:
                std::unique_ptr<UplinkEvent> jump = std::make_unique<UplinkEvent>(std::dynamic_pointer_cast<Object::Uplink>(interaction));
                throw EventException("Jump Event Executed", true);
        }
    }

    InteractionEvent::~InteractionEvent()
    {
        if (variantId_ != INTERACT)
        {
            std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_) ->removeDroneState(Actors::Drone::INTERACTING);
        }
    }
};