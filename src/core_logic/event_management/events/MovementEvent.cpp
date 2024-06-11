//
// Created by keanu on 6/10/2024.
//

#include "MovementEvent.h"
#include "raylib.h"

void MovementEvent::update()
{
    /**
     * @pseudo_code, TODO: Code
     **/
    ticks++;

    if (!axisMovement)
    {
        checkStillPressed();
    }

    if (primaryDir_ == 0)
    {
        return;
    }

    if (moveRight_)
    {
        po_mainActor_->moveRight(); /**@attention: should Actor check for collision themselves?*/
    }
    if (moveLeft_)
    {
        po_mainActor_->moveLeft();
    }
    if (moveUp_)
    {
        po_mainActor_->moveUp();
    }
    if (moveDown_)
    {
        po_mainActor_->moveDown();
    }
    if (ticks % 4 == 0)
    {
        po_mainActor_->shiftFrame(WALKING, primaryDir);
    }

}

void MovementEvent::startMove(EventEnum pa_Event, bool pa_axisMovement)
{
    /**
     * @pseudo_code, TODO: Code
     **/
    bool moveUp_;
    bool moveDown_;
    bool moveLeft_;
    bool moveRight_;

    /**
    *@TODO: Rewrite to map<MoveEvent, bool>
    **/

    bool axisMovement_ = pa_axisMovement;

    if (primaryDir_ == 0)
    {
        primaryDir_ = pa_Event;
        ticksStart();
    }
    switch (pa_Event)
    {
        case MOVEUP_EVENT:
            moveUp_ = true;
            break;
        case MOVEDOWN_EVENT:
            moveDown_ = true;
            break;
        case MOVELEFT_EVENT:
            moveLeft_ = true;
            break;
        case MOVERIGHT_EVENT:
            moveRight_ = true;
            break;
        default:
            throw std::EventException("Unknown Direction");
            break;
    }
}
