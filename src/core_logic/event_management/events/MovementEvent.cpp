//
// Created by keanu on 6/10/2024.
//

#include <map>
#include "MovementEvent.h"
#include "raylib.h"
#include "event_management/EventUtilities.h"
#include "event_management/actor/Drone.h"
#include "data_processing/Store.h"

/**
 *@todo: test
 **/

void CoreLogic::EventManagement::MovementEvent::update()
{
    /**
     * @note: should work
     **/

    checkStillPressed();
    if (!ticksRunning_)
    {
        return;
    }

        ticks_++;




    dynamic_pointer_cast<Actors::Drone>(po_mainActor_)->move(directionMap_[MOVE_UP], directionMap_[MOVE_DOWN], directionMap_[MOVE_LEFT], directionMap_[MOVE_RIGHT]);

    /**
     * @note: add facing direction variable and func call for actor
     **/

    if (ticks_ % 4 == 0)
    {
        /**
         *@todo: shift Frame to be implemented into actors with states
         **/
        po_mainActor_->shiftFrame(WALKING, primaryDir);
    }

}

void CoreLogic::EventManagement::MovementEvent::startMove(CoreLogic::EventManagement::EventEnum pa_Event)
{
    /**
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

    if (primaryDir_ == EVENT_NULL)
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
    if (directionMap_.at(MOVE_UP) && (inputHandler_.isCommandReleased(MOVE_UP)))
    {
        directionMap_.at(MOVE_UP) = false;
        if (primaryDir_ == MOVE_UP)
        {
            newPrimary = true;
        }
    }
    if (directionMap_.at(MOVE_DOWN) && (inputHandler_.isCommandReleased(MOVE_DOWN)))
    {
        directionMap_.at(MOVE_DOWN) = false;
        if (primaryDir_ == MOVE_DOWN)
        {
            newPrimary = true;
        }
    }
    if (directionMap_.at(MOVE_LEFT) && (inputHandler_.isCommandReleased(MOVE_LEFT)))
    {
        directionMap_.at(MOVE_LEFT) = false;
        if (primaryDir_ == MOVE_LEFT)
        {
            newPrimary = true;
        }
    }
    if (directionMap_.at(MOVE_RIGHT) && (inputHandler_.isCommandReleased(MOVE_RIGHT)))
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

CoreLogic::EventManagement::MovementEvent::MovementEvent(): Event(MOVE_UP)
{
    po_mainActor_ = CoreLogic::DataProcessing::ActorStorage::getPlayer();
    primaryDir_ = EVENT_NULL;
    ticksRunning_ = false;
    directionMap_ = {{MOVE_UP, false}, {MOVE_DOWN, false}, {MOVE_LEFT, false}, {MOVE_RIGHT, false}};
}





