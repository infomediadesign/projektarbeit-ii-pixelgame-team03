//
// Created by keanu on 6/18/2024.
//

#ifndef HIVE_EVENTUTILITIES_H
#define HIVE_EVENTUTILITIES_H

namespace CoreLogic::EventManagement
{
    enum EventEnum {
        EVENT_NULL,
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,

        INTERACT,


        ABILITY,
        CLEAN,
        PUSH,


        DEATH_ABILITY,
        DISCONNECT,

        HIGHLIGHT,
        PAUSE
    };
}

#endif //HIVE_EVENTUTILITIES_H
