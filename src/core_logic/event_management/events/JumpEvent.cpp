//
// Created by keanu on 8/31/2024.
//

#include "JumpEvent.h"
#include "actors/MovableActor.h"
#include "actors/Drone.h"

CoreLogic::EventManagement::JumpEvent::JumpEvent(std::shared_ptr<Object::JumpPoint> pa_jumpPoint) : AbilityEvent(JUMP)
{
    /**
     * @Pseudo_Code: JumpPoint not yet existing, neither is getJumpPosition()
     * @todo: Code JumpPoint and getJumpPosition()
     */
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
    Vector2 position = pa_jumpPoint->getJumpPosition();
    std::dynamic_pointer_cast<CoreLogic::EventManagement::Actors::MovableActor>(po_mainActor_) ->setPosition(position);
}

CoreLogic::EventManagement::JumpEvent::~JumpEvent()
{
    std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_) ->removeDroneState(Actors::Drone::JUMP);
}
