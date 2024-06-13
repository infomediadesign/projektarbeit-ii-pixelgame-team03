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
    if (ticksRunning_)
    {
        ticks++;
    }
    if (!axisMovement)
    {
        checkStillPressed();
    } else {
        updateAxis();
    }

    if (primaryDir_ == 0)
    {
        return;
    }

    /**
     *@note: We still have to figure out how to handle directions cleanly for all classes
     **/
    if (moveUp || moveDown || moveLeft || moveRight)
    {
        po_mainActor_->move(moveUp, moveDown, moveLeft, moveRight);
    }

    if (ticks % 4 == 0)
    {
        po_mainActor_->shiftFrame(WALKING, primaryDir);
    }

}

void MovementEvent::startMove(EventEnum pa_Event)
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

    if (primaryDir_ == 0)
    {
        primaryDir_ = pa_Event;
        ticksRunning_ = true;
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

void MovementEvent::checkStillPressed()
{
    /**
     *@pseudo_code, TODO: Code
     **/

    bool newPrimary = false;

    /**
     *@attention: It assumes here that the InputHandler gives the Option to handle an Axis like a Button
     **/
    if (moveUp_ && (IsKeyReleased(InputHandler.getKey(UP)) || IsGamepadButtonReleased(gamepad, InputHandler.getButton(UP))
                    || InputHandler.isAxisReleased(UP)))
    {
        moveUp_ = false;
        if (primaryDir_ == MOVEUP_EVENT)
        {
            newPrimary = true;
        }
    }
    if (moveDown_ && (IsKeyReleased(InputHandler.getKey(DOWN)) || IsGamepadButtonReleased(gamepad, InputHandler.getButton(DOWN))
                      || InputHandler.isAxisReleased(DOWN)))
    {
        moveDown_ = false;
        if (primaryDir_ == MOVEDOWN_EVENT)
        {
            newPrimary = true;
        }
    }
    if (moveLeft_ && (IsKeyReleased(InputHandler.getKey(LEFT)) || IsGamepadButtonReleased(gamepad, InputHandler.getButton(LEFT))
                      || InputHandler.isAxisReleased(LEFT)))
    {
        moveLeft_ = false;
        if (primaryDir_ == MOVELEFT_EVENT)
        {
            newPrimary = true;
        }
    }
    if (moveRight_ && (IsKeyReleased(InputHandler.getKey(RIGHT)) || IsGamepadButtonReleased(gamepad, InputHandler.getButton(RIGHT))
                       || InputHandler.isAxisReleased(RIGHT)))
    {
        moveRight_ = false;
        if (primaryDir_ == MOVERIGHT_EVENT)
        {
            newPrimary = true;
        }
    }
    if (newPrimary)
    {
        if (moveUp_)
        {
            primaryDir_ = MOVEUP_EVENT;
        } else if (moveDown_) {
            primaryDir_ = MOVEDOWN_EVENT;
        } else if (moveLeft_) {
            primaryDir_ = MOVELEFT_EVENT;
        } else if (moveRight_) {
            primaryDir_ = MOVERIGHT_EVENT;
        } else {
            primaryDir_ = 0;
            ticksRunning_ = false;
        }
    }
}





