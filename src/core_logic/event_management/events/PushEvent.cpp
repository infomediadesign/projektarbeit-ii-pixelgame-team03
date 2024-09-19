//
// Created by keanu on 8/29/2024.
//

#include "PushEvent.h"
#include "data_processing/Store.h"
#include "EventHandler.h"
#include "actors//objects/Cliff.h"
#include "SoundHandler.h"


namespace CoreLogic::EventManagement
    {
        PushEvent::PushEvent(std::shared_ptr<Object::Boulder> pa_pushable) : AbilityEvent(PUSH)
        {
            po_pushable_ = pa_pushable;
            std::vector<std::shared_ptr<Actor>> &barriers = CoreLogic::DataProcessing::ActorStorage::getCollidables()->at(po_pushable_->getElevation());
            Rectangle destination = po_pushable_ -> getHitbox();
            switch (po_mainActor_->getPrimaryDirection())
            {
                case UserInterface::Direction::UP:
                    destination.y -= CoreLogic::DataProcessing::global_tileSize;
                    break;

                case UserInterface::Direction::DOWN:
                    destination.y += CoreLogic::DataProcessing::global_tileSize;
                    break;
                case UserInterface::Direction::LEFT:
                    destination.x -= CoreLogic::DataProcessing::global_tileSize;
                    break;
                case UserInterface::Direction::RIGHT:
                    destination.x += CoreLogic::DataProcessing::global_tileSize;
                    break;
            }
            for (std::shared_ptr<Actor> &barrier : barriers)
            {
                if (barrier == nullptr)
                {
                    continue;
                }
                if (std::dynamic_pointer_cast<Actor>(barrier) -> getId() == std::dynamic_pointer_cast<Actor>(po_mainActor_)->getId())
                {
                    continue;
                }
                if (barrier->getId() == po_pushable_->getId())
                {
                    continue;
                }
                if (std::dynamic_pointer_cast<Actor>(barrier) -> getCollisionType() == Actor::CollisionType::NONE)
                {
                    continue;
                }



                if (CheckCollisionRecs(destination, barrier->getHitbox()))
                {
                    throw EventException("Collision with barrier", false);
                }
            }
            ticks_ = 30;
            frameCount_ = 30/ po_mainActor_->getSprite().getFrameAmount(1)*2+1;
            std::vector<std::shared_ptr<Object::Cliff>> cliffs = CoreLogic::DataProcessing::ActorStorage::getCliffs()->at(po_pushable_ ->getElevation());

            bool cliffPush = false;
            if (cliffs.size() != 0)
            {
                for (auto &cliff: cliffs)
                {
                    if (cliff == nullptr)
                    {
                        continue;
                    }
                    Rectangle cliffHitbox = cliff->getHitbox();

                    if (CheckCollisionRecs(cliffHitbox, destination))
                    {
                        cliffPush = true;
                        break;
                    }
                }
            }

            float mult = 1;
            cliffPush ? mult = 2 : mult = 1;
            switch (po_mainActor_->getPrimaryDirection())
            {
                case CoreLogic::UserInterface::Direction::UP:
                    push_ = {0, -12 * mult};
                    break;
                case CoreLogic::UserInterface::Direction::DOWN:
                    push_ = {0, 12 * mult};
                    break;
                case CoreLogic::UserInterface::Direction::LEFT:
                    push_ = {-12 * mult, 0};
                    break;
                case CoreLogic::UserInterface::Direction::RIGHT:
                    push_ = {12 * mult, 0};
                    break;
            }

        }

        PushEvent::~PushEvent()
        {

            auto& eventHandler = EventHandler::getInstance();

            std::vector<std::shared_ptr<Object::Cliff>> cliffs = CoreLogic::DataProcessing::ActorStorage::getCliffs()->at(po_pushable_ ->getElevation());


            if (cliffs.size() == 0)
            {
                return;
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
                    po_pushable_ -> setCliff(cliff);
                    eventHandler.handleEvents({FALLING}, po_pushable_->getId());
                    return;
                }
            }

        }

        void PushEvent::update()
        {
            if (ticks_ == 30)
            {
              auto &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
                soundHandler.playSound(SoundHandler::PUSH);
            }
            if (ticks_ % frameCount_ == 0)
            {
                po_mainActor_->shiftFrame(1);
            }

            Rectangle destination = po_pushable_ -> getHitbox();

            switch (ticks_)
            {
                case 21:
                    destination.x += push_.x;
                    destination.y += push_.y;
                    push_.x /= 2;
                    push_.y /= 2;
                    po_pushable_->setPosition({destination.x, destination.y});
                    break;
                case 12:
                    destination.x += push_.x;
                    destination.y += push_.y;
                    push_.x /= 2;
                    push_.y /= 2;
                    po_pushable_->setPosition({destination.x, destination.y});
                    break;
                case 6:
                    destination.x += push_.x;
                    destination.y += push_.y;
                    po_pushable_->setPosition({destination.x, destination.y});
                    break;
            }



            if (ticks_ == 0)
            {
                destination.x += push_.x;
                destination.y += push_.y;
                po_pushable_->setPosition({destination.x, destination.y});
                throw EventException("Push Event Executed", true);
            }
            ticks_--;
        }
    } // CoreLogic
// EventManagement