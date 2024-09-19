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
            ticks_ = 30;
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
            if (ticks_ % 20 == 0)
            {
                po_mainActor_->shiftFrame(1);
            }



            Rectangle destination = po_barrel_ -> getHitbox();

            switch (ticks_)
            {
                case 21:
                    destination.x += push_.x;
                    destination.y += push_.y;
                    push_.x /= 2;
                    push_.y /= 2;
                    break;
                case 12:
                    destination.x += push_.x;
                    destination.y += push_.y;
                    push_.x /= 2;
                    push_.y /= 2;
                    break;
                case 6:
                    destination.x += push_.x;
                    destination.y += push_.y;
                    break;
            }

            po_barrel_->setPosition({destination.x, destination.y});

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