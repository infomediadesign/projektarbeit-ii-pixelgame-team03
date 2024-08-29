//
// Created by keanu on 8/2/2024.
//

#include "CleaningEvent.h"
#include "actors/Drone.h"
#include "data_processing/Store.h"

CoreLogic::EventManagement::CleaningEvent::CleaningEvent(): AbilityEvent(CLEAN)
{
    po_mainActor_ = std::dynamic_pointer_cast<Actor>(CoreLogic::DataProcessing::ActorStorage::getPlayer());
    po_rubble_ = std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_)->getAbility();
    ticks_ = 100;
}

void CoreLogic::EventManagement::CleaningEvent::update()
{
    /**
     * @todo: Some kinks yet to review:
     * @first: rubble -> setCleaned
     * @second: shiftFrame for working number
     */
    if (ticks_ % 20 == 0)
    {
        po_mainActor_->shiftFrame(/**@Attention: set to working frames*/);
    }
    ticks_--;
    if (ticks_==0)
    {
        po_rubble_->setCleaned();
        throw true;
    }
}
