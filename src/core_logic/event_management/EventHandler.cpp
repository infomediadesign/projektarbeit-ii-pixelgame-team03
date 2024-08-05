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

CoreLogic::EventManagement::EventHandler &CoreLogic::EventManagement::EventHandler::getInstance()
{
    static CoreLogic::EventManagement::EventHandler instance;
    return instance;
}

void CoreLogic::EventManagement::EventHandler::handleEvents(const std::vector<EventEnum> &pa_thrownEvents, int pa_actorID)
{
    /**
     * @note: Could go back to bitwise Eventhandling via actor-id-map (one int of active Events per Actor)
     * @attention: Either must go back to bitwise or must introduce a map<int, vector<EventEnum>> for the eventIDs and
     *             would need 3 for-loops
     * @attention: Should collect activeEvents probably also as map<int, vector<Event>> so it is easier to track?
     * @TODO: check with Josi
     **/


    std::lock_guard<std::mutex> lock(eventHandler_mutex_);
    bool isActive = false;
    auto it = po_activeEvents_.find(pa_actorID);
    if (!(it != po_activeEvents_.end()))
    {
        po_activeEvents_.insert({pa_actorID, std::vector<std::unique_ptr<Event>>(15)});
    }


    for (auto &thrownEvent: pa_thrownEvents)
    {
        if ((thrownEvent == MOVE_UP || thrownEvent == MOVE_DOWN || thrownEvent == MOVE_LEFT || thrownEvent == MOVE_RIGHT) && pa_actorID==0)
        {
            try
            {
                activateEvent(thrownEvent);
            } catch (std::exception &e) {
                TraceLog(LOG_INFO, e.what());
            }
            continue;
        }

        for (auto &activeEvent: po_activeEvents_[pa_actorID])
        {
            if (activeEvent == nullptr)
            {
                continue;
            }
            if (thrownEvent == activeEvent->getID())
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
     * @attention: Outdated looping
     **/
    /*for (auto &thrownEvent: pa_thrownEvents)
    {
        for (auto &activeEventID: *activeEventIDs_)
        {
            if (pa_actorID == activeEventID.first && thrownEvent == activeEventID.second)
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
    try
    {
        po_movementEvent_ -> update();
    } catch (std::exception &e) {
        /**
         * @attention: could use Exception Handling to deactivate Events
         **/
        TraceLog(LOG_INFO, e.what());
    }

    for (auto &activeEvent: po_activeEvents_)
    {
        for (auto &event: activeEvent.second)
        {
            if (event == nullptr)
            {
                continue;
            }
            try
            {
                event -> update();
            } catch (std::exception &e) {
                /**
                * @attention: could use Exception Handling to deactivate Events
                **/
                TraceLog(LOG_INFO, e.what());
            }

        }
    }

}

void CoreLogic::EventManagement::EventHandler::activateEvent(EventEnum pa_activateEvent)
{
    /**
     *@pseudo_code, TODO: Code
     **/

    if (pa_activateEvent == MOVE_UP || pa_activateEvent == MOVE_DOWN || pa_activateEvent == MOVE_LEFT || pa_activateEvent == MOVE_RIGHT)
    {
        if (!movementBlocked_)
        {
            po_movementEvent_ -> startMove(pa_activateEvent);
            return;
        } else {
            throw std::runtime_error("Movement Blocked");
        }
        TraceLog(LOG_ERROR, "reached unreachable Code");
    } else if (pa_activateEvent == PAUSE) {
        return;
    } else if (pa_activateEvent == EVENT_NULL) {
        return;
    } else {
        throw std::runtime_error("Not Handled Event");
    }


}

void CoreLogic::EventManagement::EventHandler::deactivateEvent(EventEnum pa_deactivateEvent)
{

}



