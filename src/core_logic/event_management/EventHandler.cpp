//
// Created by keanu on 6/9/2024.
//

#include <iostream>
#include "EventHandler.h"
#include "raylib.h"
#include "EventUtilities.h"

std::mutex CoreLogic::EventManagement::EventHandler::eventHandler_mutex_;
CoreLogic::EventManagement::EventHandler::EventHandler()
{
    po_movementEvent_ = std::make_unique<MovementEvent>();
}

CoreLogic::EventManagement::EventHandler::~EventHandler()
{

}

void CoreLogic::EventManagement::EventHandler::handleEvents(std::vector<EventEnum> pa_thrownEvents, int pa_actorID)
{
    /**
     * @note: Could go back to bitwise Eventhandling via actor-id-map (one int of active Events per Actor)
     * @TODO: check with Josi
     **/

    std::lock_guard<std::mutex> lock(eventHandler_mutex_);
    bool isActive = false;
    int actorId = pa_actor.getId();
    for (auto &thrownEvent: pa_thrownEvents)
    {
        for (auto &activeEventID: *activeEventIDs_)
        {
            if (actorId == activeEventID.first && thrownEvent == activeEventID.second)
            {
                isActive = true;
                break;
            }
        }
        if (!isActive)
        {
            try
            {
                activateEvent(thrownEvent);
            } catch (std::exception &e) //@TODO: write Exception Handling for Events
            {
                TraceLog(LOG_INFO, e.what());
            }
        }
    }


    /**
     * @brief: Bitwise Enum saving saves a whole outter for-Loop which significantly lowers Iterations
     * @date: 10.06.2024
     * @attention: Outdated
     **/
   /* int bit_count = 8;
    activeEventIDs_ |= pa_thrownEvents;
    for (int bit = 1, count = 0; count < bit_count; bit <<= 1, count++)
    {
        if ((activeEventIDs_ & bit) != 0)
        {
            try
            {
                activateEvent(static_cast<EventEnum>(bit));
            } catch (std::exception &e) //@TODO: write Exception Handling for Events
            {
                TraceLog(LOG_INFO, e.what());
            }
            continue;
        }
        if ((deactivateEventIDs_ & bit) != 0)
        {
            deactivateEvent(static_cast<EventEnum>(bit));
        }
        
    }*/


    /**
     * @attention: This commented section below is the old version of handleEvents(),
     *              with the double for-loops for enum Arrays
     *
     **/
    /*for (auto &thrownEvent: events)
    {
        bool isActive = false;
        for (auto &activeEvent: *activeEventIDs_)
        {
            if (thrownEvent == activeEvent)
            {
                isActive = true;
                break;
            }
        }
        if (!isActive)
        {
            try
            {
                activateEvent(thrownEvent);
            } catch (std::exception &e) //@TODO: write Exception Handling for Events
            {
                TraceLog(LOG_INFO, e.what());
            }
        }
    }*/
}

void CoreLogic::EventManagement::EventHandler::update()
{
    for (auto &activeEvent: *activeEvents_)
    {
        try
        {
            activeEvent.update();
        } catch (std::exception &e) //@TODO: write Exception Handling for Events
        {
            TraceLog(LOG_INFO, e.what());

        }
    }
}

void CoreLogic::EventManagement::EventHandler::activateEvent(EventEnum pa_activateEvent)
{
    /**
     *@pseudo_code, TODO: Code
     **/

    switch (pa_activateEvent)
    {
        case (MOVE_DOWN || MOVE_UP || MOVE_LEFT || MOVE_RIGHT):
            if (!movementBlocked_)
            {
                po_movementEvent_ -> startMove(pa_activateEvent);
                return;
            } else {
                throw std::runtime_error("Movement Blocked");
            }
            TraceLog(LOG_ERROR, "reached unreachable Code");
            break;

        case PAUSE:
            break;
        case EVENT_NULL:
            break;
        default:
            throw std::runtime_error("Undefined Event");
    }

}

void CoreLogic::EventManagement::EventHandler::deactivateEvent(EventEnum pa_deactivateEvent)
{
    
}

CoreLogic::EventManagement::EventHandler &CoreLogic::EventManagement::EventHandler::getInstance()
{
    static CoreLogic::EventManagement::EventHandler instance;
    return instance;
}



