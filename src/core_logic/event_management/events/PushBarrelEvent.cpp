//
// Created by keanu on 9/1/2024.
//

#include <stdexcept>
#include "PushBarrelEvent.h"
#include "EventHandler.h"
#include "SoundHandler.h"

namespace CoreLogic
{
    namespace EventManagement
    {
        PushBarrelEvent::PushBarrelEvent(std::shared_ptr<Object::Barrel> pa_barrel) : AbilityEvent(BARREL_PUSH)
        {
            auto &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
            soundHandler.playSound(SoundHandler::PUSH);
            po_barrel_ = pa_barrel;
            animationSpeed_ = DataProcessing::DesignConfig::PUSH_SPEED;
            animationLength_ = (po_mainActor_->getSprite().getFrameAmount(1) * animationSpeed_)/2 - 1;
            ticks_ = animationLength_;
            switch (po_barrel_->getPrimaryDirection())
            {
                case CoreLogic::UserInterface::Direction::UP:
                    throw EventException("PushBarrelEvent: barrel cannot be pushed up", true);
                case CoreLogic::UserInterface::Direction::DOWN:
                    push_ = {0, 12};
                    break;
                case CoreLogic::UserInterface::Direction::LEFT:
                    push_ = {-12, 0};
                    break;
                case CoreLogic::UserInterface::Direction::RIGHT:
                    push_ = {12, 0};
                    break;
            }
        }

        PushBarrelEvent::~PushBarrelEvent()
        {
            auto& eventHandler = EventHandler::getInstance();
            eventHandler.handleEvents({FALLING}, po_barrel_ -> getId());
        }

        void PushBarrelEvent::update()
        {
            if (ticks_ % animationSpeed_ == 0)
            {
                po_mainActor_->shiftFrame(1);
            }



            Rectangle destination = po_barrel_ -> getHitbox();

            if (ticks_== ((int)animationLength_/3)*2)
            {
                destination.x += push_.x;
                destination.y += push_.y;
                push_.x /= 2;
                push_.y /= 2;
                po_barrel_->setPosition({destination.x, destination.y});

            }else if(ticks_ == (int)animationLength_/3) {
                destination.x += push_.x;
                destination.y += push_.y;
                push_.x /= 2;
                push_.y /= 2;
                po_barrel_->setPosition({destination.x, destination.y});

            }else if (ticks_ == (int)animationLength_/6){
                destination.x += push_.x;
                destination.y += push_.y;
                po_barrel_->setPosition({destination.x, destination.y});

            }



            ticks_--;
            if (ticks_ == 0)
            {
                destination.x += push_.x;
                destination.y += push_.y;
                po_barrel_->setPosition({destination.x, destination.y});
                throw EventException("Barrel Pushed", true);
            }
        }
    } // CoreLogic
} // EventManagement