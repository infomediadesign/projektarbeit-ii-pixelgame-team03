//
// Created by keanu on 8/2/2024.
//

#include "CleaningEvent.h"
#include "actors/Drone.h"
#include "data_processing/Store.h"

CoreLogic::EventManagement::CleaningEvent::CleaningEvent(std::shared_ptr<CoreLogic::EventManagement::Object::Rubble>
        pa_rubble): AbilityEvent(CLEAN)
{
    po_rubble_ = pa_rubble;
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
