//
// Created by keanu on 6/9/2024.
//

#include <iostream>
#include "EventHandler.h"
#include "raylib.h"

EventHandler::EventHandler()
{

}

EventHandler::~EventHandler()
{

}

void EventHandler::handleEvents(int pa_thrownEvents)
{
    /**
     * @brief: Bitwise Enum saving saves a whole outter for-Loop which significantly lowers Iterations
     * @date: 10.06.2024
     *
     **/

    int bit_count = 8;
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
    }


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

void EventHandler::update()
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

void EventHandler::activateEvent(EventEnum pa_Event)
{
    /**
     *@pseudo_code, TODO: Code
     **/

    switch (pa_Event)
    {
        case MOVEDOWN_EVENT || MOVEUP_EVENT || MOVELEFT_EVENT || MOVERIGHT_EVENT:
            if (!movementBlocked)
            {
                moveEvent.startMove(pa_Event);
                return;
            } else {
                throw std::EventException("Movement Blocked");
            }
            TraceLog(LOG_ERROR, "reached unreachable Code");
            break;

        case PAUSE_EVENT:
            break;
        case EXIT_EVENT:
            break;
        case UNDEFINED_EVENT:
            break;
        default:
            throw std::EventException("Undefined Event");
    }

}

void EventHandler::deactivateEvent()
{

}



