//
// Created by keanu on 8/30/2024.
//

#include <stdexcept>
#include "FallingEvent.h"
#include "actors/MovableActor.h"
#include "Store.h"
#include "EventHandler.h"
#include "FallingBarrelEvent.h"
#include "FallingBoulderEvent.h"


CoreLogic::EventManagement::FallingEvent::~FallingEvent()
{
    po_mainActor_ -> setVisible(false);
    po_mainActor_ -> setCollisionType(Actor::CollisionType::NONE);
}

void CoreLogic::EventManagement::FallingEvent::update()
{
    if (!broken_)
    {
        fall();
    } else {
        destroy();
    }
}

CoreLogic::EventManagement::FallingEvent::FallingEvent(int pa_actorID): Event(FALLING)
{
    std::map<int, std::vector<std::shared_ptr<Object::Ability>>> &abilities = *DataProcessing::ActorStorage::getWorkerAbilities();
    for (auto &pair: abilities)
    {
        for (auto &ability: pair.second)
        {
            if (ability->getId() == pa_actorID)
            {
                po_mainActor_ = ability;
                break;
            }
        }
    }
    if (po_mainActor_ == nullptr)
    {
        throw EventException("Actor not found", false);
    }

}

void CoreLogic::EventManagement::FallingEvent::fall()
{
    if (ticks_ != 0 && ticks_ % 5 == 0)
    {
        Vector2 newPosition = po_mainActor_ -> getPosition();
        int tileSize = CoreLogic::DataProcessing::tileSize;
        newPosition.y += (0.5 * tileSize);
        std::dynamic_pointer_cast<CoreLogic::EventManagement::Actors::MovableActor>(po_mainActor_)
                -> setPosition(newPosition);
        fallenHeight_ += 0.5;
    }
    ticks_++;

    if (fallenHeight_ >= fallHeight_)
    {
        broken_ = true;
        ticks_ = 0;
    }
}


std::unique_ptr<CoreLogic::EventManagement::FallingEvent> CoreLogic::EventManagement::FallingEvent::transform()
{
    if (std::dynamic_pointer_cast<Object::Ability>(po_mainActor_) -> getAbilityType() == Object::Ability::AbilityType::PUSH)
    {
        return std::make_unique<FallingBoulderEvent>(std::dynamic_pointer_cast<Object::Boulder>(po_mainActor_));
    } else if (std::dynamic_pointer_cast<Object::Ability>(po_mainActor_) -> getAbilityType() == Object::Ability::AbilityType::BARREL) {
        return std::make_unique<FallingBarrelEvent>(std::dynamic_pointer_cast<Object::Barrel>(po_mainActor_));
    }
    throw EventException("Ability not found", false);
}
