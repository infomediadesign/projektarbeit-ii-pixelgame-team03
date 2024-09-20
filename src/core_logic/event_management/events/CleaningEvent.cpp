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
    animationSpeed_ = DataProcessing::DesignConfig::RUBBLE_CLEANING_SPEED;
    animationLength_ = (po_mainActor_->getSprite().getFrameAmount(1) * animationSpeed_)/2-1;

    rubbleBreakRate_ = animationLength_/po_rubble_->getSprite().getFrameAmount(1)+1;
}

void CoreLogic::EventManagement::CleaningEvent::update()
{
    if (ticks_ % animationSpeed_ == 0)
    {
        po_mainActor_->shiftFrame(1);
    }
    if (ticks_ % rubbleBreakRate_==0)
    {
        po_rubble_->shiftFrame(1);
    }
    if (ticks_ == animationSpeed_)
    {
        auto &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
        soundHandler.playSound(SoundHandler::RUBBLE);
    }
    ticks_++;
    if (ticks_==animationLength_)
    {
        po_rubble_->setCleaned();
        throw EventException("Rubble Cleaned", true);
    }
}
