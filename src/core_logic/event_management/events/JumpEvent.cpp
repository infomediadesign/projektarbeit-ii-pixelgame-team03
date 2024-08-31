//
// Created by keanu on 8/31/2024.
//

#include "JumpEvent.h"
#include "actors/MovableActor.h"

CoreLogic::EventManagement::JumpEvent::JumpEvent(std::shared_ptr<JumpPoint> pa_jumpPoint) : AbilityEvent(JUMP)
{
    /**
     * @Pseudo_Code: JumpPoint not yet existing, neither is getJumpPosition()
     * @todo: Code JumpPoint and getJumpPosition()
     */
    Vector2 position = pa_jumpPoint->getJumpPosition();
    std::dynamic_pointer_cast<CoreLogic::EventManagement::Actors::MovableActor>(po_mainActor_) ->setPosition(position);
}
