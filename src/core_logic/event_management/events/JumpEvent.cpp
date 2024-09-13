//
// Created by keanu on 8/31/2024.
//

#include "JumpEvent.h"
#include "actors/MovableActor.h"
#include "actors/Drone.h"

CoreLogic::EventManagement::JumpEvent::JumpEvent(std::shared_ptr<Object::JumpPoint> pa_jumpPoint) : AbilityEvent(JUMP)
{

    try
    {
        std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_) -> setDroneState(Actors::Drone::JUMP);
    } catch (EventException &e)
    {
        if (!e.wasSuccessful())
        {
            throw e;
        }
    }
    Vector2 destination = pa_jumpPoint->getJumpPosition();
    int elevation = po_mainActor_->getElevation();
    std::vector<std::shared_ptr<Actor>> barriers = CoreLogic::DataProcessing::ActorStorage::getCollidables()->at(elevation);
    if (!barriers.empty())
    {
        for (auto &barrier: barriers)
        {
            if (barrier == nullptr)
            {
                continue;
            }
            if (barrier->getElevation() != elevation)
            {
                continue;
            }
            if (barrier->getCollisionType() == Actor::CollisionType::NONE)
            {
                continue;
            }
            Rectangle barrierHitbox = barrier->getHitbox();
            Rectangle playerHB = po_mainActor_->getHitbox();
            Rectangle destinationHB = {destination.x, destination.y, playerHB.width, playerHB.height};
            if (CheckCollisionRecs(barrierHitbox, destinationHB))
            {
                throw EventException("Climbing Event Failed", false);
            }
        }
    }
    std::dynamic_pointer_cast<CoreLogic::EventManagement::Actors::MovableActor>(po_mainActor_) ->setPosition(destination);
}

CoreLogic::EventManagement::JumpEvent::~JumpEvent()
{
    std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_) ->removeDroneState(Actors::Drone::JUMP);
}
