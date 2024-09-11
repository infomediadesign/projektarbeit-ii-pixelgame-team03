//
// Created by keanu on 6/10/2024.
//

#include <map>
#include "MovementEvent.h"
#include "raylib.h"
#include "event_management/EventUtilities.h"
#include "event_management/actors/Drone.h"
#include "data_processing/Store.h"
#include "Sprite.h"
#include "Event.h"


void CoreLogic::EventManagement::MovementEvent::update()
{
    checkStillPressed();
    if (!std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_)->canMove())
    {
//        stop();
        throw EventException("Drone cannot move", true);
    }
    if (!ticksRunning_)
    {
        po_mainActor_->resetFrame(0);
        return;
    }

        ticks_++;

    std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_)->move(directionMap_[MOVE_UP], directionMap_[MOVE_DOWN], directionMap_[MOVE_LEFT], directionMap_[MOVE_RIGHT]);

    /**
     * @note: add facing direction variable and func call for actor
     **/

    if (ticks_ % 3 == 0)
    {
        po_mainActor_->shiftFrame(0);
    }
}

void CoreLogic::EventManagement::MovementEvent::updateActorDir()
{
    switch (primaryDir_)
    {
        case MOVE_UP:
            po_mainActor_->setPrimaryDirection(CoreLogic::UserInterface::Direction::UP);
            break;
        case MOVE_DOWN:
            po_mainActor_->setPrimaryDirection(CoreLogic::UserInterface::Direction::DOWN);
            break;
        case MOVE_LEFT:
            po_mainActor_->setPrimaryDirection(CoreLogic::UserInterface::Direction::LEFT);
            break;
        case MOVE_RIGHT:
            po_mainActor_->setPrimaryDirection(CoreLogic::UserInterface::Direction::RIGHT);
            break;
        default:
            break;
    }
}

void CoreLogic::EventManagement::MovementEvent::startMove(CoreLogic::EventManagement::EventEnum pa_Event)
{
    /*if (!std::dynamic_pointer_cast<Actors::Drone>(po_mainActor_)->canMove())
    {
        throw EventException("Drone can't move", false);
    }*/

    if (primaryDir_ == EVENT_NULL)
    {
        primaryDir_ = pa_Event;
        ticksRunning_ = true;
    }

    directionMap_[pa_Event] = true;
    updateActorDir();
    po_mainActor_->shiftFrame(0);
}

void CoreLogic::EventManagement::MovementEvent::checkStillPressed()
{
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
            updateActorDir();
            po_mainActor_->shiftFrame(0);
        } else if (directionMap_.at(MOVE_DOWN)) {
            primaryDir_ = MOVE_DOWN;
            updateActorDir();
            po_mainActor_->shiftFrame(0);
        } else if (directionMap_.at(MOVE_LEFT)) {
            primaryDir_ = MOVE_LEFT;
            updateActorDir();
            po_mainActor_->shiftFrame(0);
        } else if (directionMap_.at(MOVE_RIGHT)) {
            primaryDir_ = MOVE_RIGHT;
            updateActorDir();
            po_mainActor_->shiftFrame(0);
        } else {
            stop();
        }
    }
}

CoreLogic::EventManagement::MovementEvent::MovementEvent(): Event(MOVE_UP)
{
    po_mainActor_ = std::dynamic_pointer_cast<Actor>(CoreLogic::DataProcessing::ActorStorage::getPlayer());
    primaryDir_ = EVENT_NULL;
    ticksRunning_ = false;
    directionMap_ = {{MOVE_UP, false}, {MOVE_DOWN, false}, {MOVE_LEFT, false}, {MOVE_RIGHT, false}};
}

void CoreLogic::EventManagement::MovementEvent::updateMainActor()
{
    po_mainActor_ = std::dynamic_pointer_cast<Actor>(CoreLogic::DataProcessing::ActorStorage::getPlayer());
    primaryDir_ = EVENT_NULL;
    ticksRunning_ = false;
    directionMap_ = {{MOVE_UP, false}, {MOVE_DOWN, false}, {MOVE_LEFT, false}, {MOVE_RIGHT, false}};
}

void CoreLogic::EventManagement::MovementEvent::stop()
{
    primaryDir_ = EVENT_NULL;
    ticksRunning_ = false;
    ticks_ = 0;
}





