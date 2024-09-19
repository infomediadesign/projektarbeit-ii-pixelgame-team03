//
// Created by keanu on 8/2/2024.
//

#include "CleaningEvent.h"
#include "actors/Drone.h"
#include "data_processing/Store.h"
#include "SoundHandler.h"

CoreLogic::EventManagement::CleaningEvent::CleaningEvent(std::shared_ptr<CoreLogic::EventManagement::Object::Rubble>
        pa_rubble): AbilityEvent(CLEAN)
{
    po_rubble_ = pa_rubble;
    ticks_ = 0;
    rubbleBreakRate_ = 50/po_rubble_->getSprite().getFrameAmount(1)+1;
}

void CoreLogic::EventManagement::CleaningEvent::update()
{
    if (ticks_ % 10 == 0)
    {
        po_mainActor_->shiftFrame(1);
    }
    if (ticks_ % rubbleBreakRate_==0)
    {
        po_rubble_->shiftFrame(1);
    }
    if (ticks_ == 10)
    {
        auto &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
        soundHandler.playSound(SoundHandler::RUBBLE);
    }
    ticks_++;
    if (ticks_==50)
    {
        po_rubble_->setCleaned();
        throw EventException("Rubble Cleaned", true);
    }
}
