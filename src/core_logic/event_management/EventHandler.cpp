//
// Created by keanu on 6/9/2024.
//

#include <iostream>
#include "EventHandler.h"
#include "raylib.h"
#include "EventUtilities.h"
#include "Event.h"
#include "events/AbilityEvent.h"

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
    std::lock_guard<std::mutex> lock(eventHandler_mutex_);
    bool isActive = false;
    auto it = po_activeEvents_.find(pa_actorID);
    if (!(it != po_activeEvents_.end()))
    {
        po_activeEvents_.insert({pa_actorID, std::vector<std::unique_ptr<Event>>(15)});
    }

    for (auto &thrownEvent: pa_thrownEvents)
    {
        isActive = false;
        if ((thrownEvent == MOVE_UP || thrownEvent == MOVE_DOWN || thrownEvent == MOVE_LEFT || thrownEvent == MOVE_RIGHT) && pa_actorID==0)
        {
            try
            {
                activateEvent(thrownEvent, pa_actorID);
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
                activateEvent(thrownEvent, pa_actorID);
            } catch (std::exception &e) //@TODO: write Exception Handling for Events
            {
                TraceLog(LOG_INFO, e.what());
            }
        }
    }
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
            } catch (bool flag) {
                if (flag)
                {
                    deactivateEvent(event->getID(),activeEvent.first);
                }
            }

        }
    }

}

void CoreLogic::EventManagement::EventHandler::activateEvent(EventEnum pa_activateEvent, int pa_actorID)
{
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
    } else if (pa_activateEvent == ABILITY) {
        /**
         * @warning: Pseudo Code
         * @TODO: Implement correctly
         */

        std::unique_ptr<AbilityEvent> ability = std::make_unique<AbilityEvent>();
        /**
         * @Warning: exception handling?
         */
        try {
            ability = ability->transform();
        } catch (std::exception &e) {
            TraceLog(LOG_ERROR, e.what());
            return;
        }
        po_activeEvents_[pa_actorID].push_back(std::move(ability));
        return;
    } else if (pa_activateEvent == EVENT_NULL) {
        return;
    } else {
        throw std::runtime_error("Not Handled Event");
    }
}

void CoreLogic::EventManagement::EventHandler::deactivateEvent(EventEnum pa_deactivateEvent, int pa_actorID)
{
    for (auto it = po_activeEvents_[pa_actorID].begin(); it != po_activeEvents_[pa_actorID].end(); ++it) {
        if (*it == nullptr)
        {
            continue;
        }
        if (it->get() -> getID() == pa_deactivateEvent)
        {
            /**
             * @Pseudo_Code: finish() or destructor
             */
            po_activeEvents_[pa_actorID].erase(it);
            break;
        }
    }
}

void CoreLogic::EventManagement::EventHandler::switchLevels()
{
    po_movementEvent_->updateMainActor();
}



