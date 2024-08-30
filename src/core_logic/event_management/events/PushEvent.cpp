//
// Created by keanu on 8/29/2024.
//

#include "PushEvent.h"
#include "Store.h"
#include "EventHandler.h"

namespace CoreLogic
{
    namespace EventManagement
    {
        PushEvent::PushEvent(std::shared_ptr<Pushable> pa_pushable) : AbilityEvent(PUSH)
        {
            po_pushable_ = pa_pushable;
            std::vector<std::shared_ptr<Barrier>> barriers = CoreLogic::DataProcessing::ActorStorage::getBarriers();
            for (std::shared_ptr<Barrier> barrier : barriers)
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
                ticks_ = 100;
            }

        }

        PushEvent::~PushEvent()
        {
            /**
             * @Pseudo_code: no Type for pushables yet, no Cliffs
             * @todo: Code Cliffs and Derived Actor Classees
             */
            auto& eventHandler = EventHandler::getInstance();
            std::vector<std::shared_ptr<Cliff>> cliffs;
            if (po_pushable_ -> getType() == PushableTypes::BARREL)
            {
                cliffs = CoreLogic::DataProcessing::ActorStorage::getCliffs();

            } else if (po_pushable_ -> getType() == PushableTypes::ROCK) {
                /**
                 * @Pseudo_code: no Falling triggers
                 * @todo: Code Falling Triggers
                 */
                cliffs = CoreLogic::DataProcessing::ActorStorage::getFallingTriggers();

            }
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
                po_mainActor_->shiftFrame(/**@Attention: set to working frames*/);
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
                case 75:
                    destination.x += push.x;
                    destination.y += push.y;
                    push.x /= 2;
                    push.y /= 2;
                    break;
                case 50:
                    destination.x += push.x;
                    destination.y += push.y;
                    push.x /= 2;
                    push.y /= 2;
                    break;
                case 25:
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
                throw true;
            }
        }
    } // CoreLogic
} // EventManagement