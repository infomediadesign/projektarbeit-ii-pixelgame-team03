//
// Created by keanu on 8/29/2024.
//

#include "PushEvent.h"
#include "Store.h"
#include "EventHandler.h"
#include "Cliff.h"


namespace CoreLogic::EventManagement
    {
        PushEvent::PushEvent(std::shared_ptr<Pushable> pa_pushable) : AbilityEvent(PUSH)
        {
            po_pushable_ = pa_pushable;
            std::vector<std::shared_ptr<Actor>> barriers = CoreLogic::DataProcessing::ActorStorage::getBarriers();
            for (std::shared_ptr<Actor> barrier : barriers)
            {
                if (barrier == nullptr)
                {
                    continue;
                }
                if (std::dynamic_pointer_cast<Actor>(barrier) -> getId() != std::dynamic_pointer_cast<Actor>(po_mainActor_)->getId())
                {
                    continue;
                }
                if (std::dynamic_pointer_cast<Actor>(barrier) -> getCollisionType() == Actor::CollisionType::NONE)
                {
                    continue;
                }

                Rectangle destination = po_pushable_ -> getHitbox();
                switch (po_mainActor_->getPrimaryDirection())
                {
                    case UserInterface::Direction::UP:
                        destination.y -= CoreLogic::DataProcessing::tileSize;
                        break;

                    case UserInterface::Direction::DOWN:
                        destination.y += CoreLogic::DataProcessing::tileSize;
                        break;
                    case UserInterface::Direction::LEFT:
                        destination.x -= CoreLogic::DataProcessing::tileSize;
                        break;
                    case UserInterface::Direction::RIGHT:
                        destination.x += CoreLogic::DataProcessing::tileSize;
                        break;
                }
                if (CheckCollisionRecs(destination, barrier->getHitbox()))
                {
                    throw std::runtime_error("Collision with barrier");
                }
                ticks_ = 30;
            }

        }

        PushEvent::~PushEvent()
        {
            /**
             * @Pseudo_code: no Type for pushables yet, no Cliffs
             * @todo: Code Cliffs and Derived Actor Classees
             */
            auto& eventHandler = EventHandler::getInstance();
            /**
             * @Pseudo_code: no Falling triggers
             * @todo: Code Falling Triggers
             */
            std::vector<std::shared_ptr<Cliff>> cliffs = CoreLogic::DataProcessing::ActorStorage::getFallingTriggers();


            if (cliffs.size() == 0)
            {
                throw std::runtime_error("No cliffs found");
            }
            for (auto& cliff : cliffs)
            {
                if (cliff == nullptr)
                {
                    continue;
                }
                Rectangle cliffHitbox = cliff -> getHitbox();

                if (CheckCollisionRecs(cliffHitbox, po_pushable_ -> getHitbox()))
                {
                    po_pushable_ -> setCliff(cliff)
                    eventHandler.handleEvents({FALLING}, po_pushable_->getId());
                    return;
                }
            }
        }

        void PushEvent::update()
        {
            if (ticks_ % 20 == 0)
            {
                po_mainActor_->shiftFrame(1);
            }

            Vector2 push;
            switch (po_mainActor_->getPrimaryDirection())
            {
                case CoreLogic::UserInterface::Direction::UP:
                    push = {0, -12};
                    break;
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
            Rectangle destination = po_pushable_ -> getHitbox();

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

            po_pushable_->setPosition(destination.x, destination.y);

            ticks_--;
            if (ticks_ == 0)
            {
                destination.x += push.x;
                destination.y += push.y;
                po_pushable_->setPosition(destination.x, destination.y);
                throw EventException("Push Event Executed");
            }
        }
    } // CoreLogic
// EventManagement