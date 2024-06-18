//
// Created by keanu on 6/10/2024.
//

#include <map>
#include "MovementEvent.h"
#include "raylib.h"
#include "event_management/EventUtilities.h"
#include "event_management/actor/Drone.h"
#include "data_processing/Store.h"
#include "EventUtilities.h"
#include "Drone.h"

void CoreLogic::EventManagement::MovementEvent::update()
{
    /**
     * @pseudo_code, TODO: Code
     **/
    if (ticksRunning_)
    {
        ticks_++;
    }

    if (primaryDir_ == 0)
    {
        return;
    }

    /**
     *@note: We still have to figure out how to handle directions cleanly for all classes
     **/

    dynamic_pointer_cast<Actors::Drone>(po_mainActor_)->move(directionMap_[MOVE_UP], directionMap_[MOVE_DOWN], directionMap_[MOVE_LEFT], directionMap_[MOVE_RIGHT]);

    if (ticks_ % 4 == 0)
    {
        po_mainActor_->shiftFrame(WALKING, primaryDir);
    }

}

void CoreLogic::EventManagement::MovementEvent::startMove(CoreLogic::EventManagement::EventEnum pa_Event)
{
    /**
     * @pseudo_code, TODO: Code
     * @note should be Coded
     **/

    /**
    *@DONE: Rewrite to map<MoveEvent, bool>
    **/

    /*
     moveUp_ = false;
     moveDown_ = false;
     moveLeft_ = false;
     moveRight_ = false;
     */

    if (primaryDir_ == 0)
    {
        primaryDir_ = pa_Event;
        ticksRunning_ = true;
    }

    directionMap_[pa_Event] = true;

    
    /*switch (pa_Event)
    {
        case MOVE_UP:
            moveUp_ = true;
            break;
        case MOVE_DOWN:
            moveDown_ = true;
            break;
        case MOVE_LEFT:
            moveLeft_ = true;
            break;
        case MOVE_RIGHT:
            moveRight_ = true;
            break;
        default:
            throw std::EventException("Unknown Direction");
            break;
    }*/
}

void CoreLogic::EventManagement::MovementEvent::checkStillPressed()
{
    /**
     *@pseudo_code, TODO: Code
     **/

    bool newPrimary = false;

    /**
     *@attention: It assumes here that the InputHandler gives the Option to handle an Axis like a Button
     **/
    if (directionMap_.at(MOVE_UP) && (InputHandler.isEventReleased(MOVE_UP)))
    {
        directionMap_.at(MOVE_UP) = false;
        if (primaryDir_ == MOVE_UP)
        {
            newPrimary = true;
        }
    }
    if (directionMap_.at(MOVE_DOWN) && (InputHandler.isEventReleased(MOVE_DOWN)))
    {
        directionMap_.at(MOVE_DOWN) = false;
        if (primaryDir_ == MOVE_DOWN)
        {
            newPrimary = true;
        }
    }
    if (directionMap_.at(MOVE_LEFT) && (InputHandler.isEventReleased(MOVE_LEFT)))
    {
        directionMap_.at(MOVE_LEFT) = false;
        if (primaryDir_ == MOVE_LEFT)
        {
            newPrimary = true;
        }
    }
    if (directionMap_.at(MOVE_RIGHT) && (InputHandler.isEventReleased(MOVE_RIGHT)))
    {
        directionMap_.at(MOVE_RIGHT) = false;
        if (primaryDir_ == MOVE_RIGHT)
        {
            newPrimary = true;
        }
    }
    if (newPrimary)
    {
        if (directionMap_.at(MOVE_UP))
        {
            primaryDir_ = MOVE_UP;
        } else if (directionMap_.at(MOVE_DOWN)) {
            primaryDir_ = MOVE_DOWN;
        } else if (directionMap_.at(MOVE_LEFT)) {
            primaryDir_ = MOVE_LEFT;
        } else if (directionMap_.at(MOVE_RIGHT)) {
            primaryDir_ = MOVE_RIGHT;
        } else {
            primaryDir_ = EVENT_NULL;
            ticksRunning_ = false;
            ticks_ = 0;
        }
    }
}

CoreLogic::EventManagement::MovementEvent::MovementEvent()
{
    po_mainActor_ = CoreLogic::DataProcessing::Player::getPlayer();
    primaryDir_ = EVENT_NULL;
    ticksRunning_ = false;
    directionMap_ = {{MOVE_UP, false}, {MOVE_DOWN, false}, {MOVE_LEFT, false}, {MOVE_RIGHT, false}};
}





