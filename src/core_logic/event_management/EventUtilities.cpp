//
// Created by keanu on 9/9/2024.
//

#include <map>
#include <string>
#include "EventUtilities.h"

namespace CoreLogic::EventManagement
{

    std::map <EventEnum, std::string> eventNames::eventNameMap = {
        {EVENT_NULL,    "EVENT_NULL"},

        {MOVE_UP,       "MOVE_UP"},
        {MOVE_DOWN,     "MOVE_DOWN"},
        {MOVE_LEFT,     "MOVE_LEFT"},
        {MOVE_RIGHT,    "MOVE_RIGHT"},

        {INTERACT,      "INTERACT"},
        {CLIMB,         "CLIMB"},
        {CHECKPOINT,    "CHECKPOINT"},
        {NOTE,          "NOTE"},

        {ABILITY,       "ABILITY"},
        {CLEAN,         "CLEAN"},
        {PUSH,          "PUSH"},
        {BARREL,        "BARREL"},
        {JUMP,          "JUMP"},
        {FALLING,       "FALLING"},

        {DEATH_ABILITY, "DEATH_ABILITY"},
        {DISCONNECT,    "DISCONNECT"},
        {ENEMY_DEATH,   "ENEMY_DEATH"},

        {VISION,        "VISION"},

        {HIGHLIGHT,     "HIGHLIGHT"},
        {PAUSE,         "PAUSE"}
    };
};