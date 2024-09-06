//
// Created by keanu on 9/1/2024.
//

#include <stdexcept>
#include "PushBarrelEvent.h"
#include "EventHandler.h"

namespace CoreLogic
{
    namespace EventManagement
    {
        PushBarrelEvent::PushBarrelEvent(std::shared_ptr<Object::Barrel> pa_barrel) : AbilityEvent(BARREL)
        {
            po_barrel_ = pa_barrel;
            ticks_ = 30;
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
                po_mainActor_->shiftFrame(/**@Attention: set to working frames*/);
            }

            Vector2 push;
            switch (po_mainActor_->getPrimaryDirection())
            {
                case CoreLogic::UserInterface::Direction::UP:
                    throw EventException("PushBarrelEvent: barrel cannot be pushed up", true);
                case CoreLogic::UserInterface::Direction::DOWN:
                    push = {0, 12};
                    break;
                case CoreLogic::UserInterface::Direction::LEFT:
                    push = {-12, 0};
                    break;
                case CoreLogic::UserInterface::Direction::RIGHT:
                    push = {12, 0};
                    break;
            }
            Rectangle destination = po_barrel_ -> getHitbox();

            switch (ticks_)
            {
                case 21:
                    destination.x += push.x;
                    destination.y += push.y;
                    push.x /= 2;
                    push.y /= 2;
                    break;
                case 12:
                    destination.x += push.x;
                    destination.y += push.y;
                    push.x /= 2;
                    push.y /= 2;
                    break;
                case 6:
                    destination.x += push.x;
                    destination.y += push.y;
                    break;
            }

            po_barrel_->setPosition({destination.x, destination.y});

            ticks_--;
            if (ticks_ == 0)
            {
                destination.x += push.x;
                destination.y += push.y;
                po_barrel_->setPosition({destination.x, destination.y});
                throw EventException("Barrel Pushed", true);
            }
        }
    } // CoreLogic
} // EventManagement