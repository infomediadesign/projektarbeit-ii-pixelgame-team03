//
// Created by keanu on 6/18/2024.
//

#ifndef HIVE_EVENTUTILITIES_H
#define HIVE_EVENTUTILITIES_H

namespace CoreLogic::EventManagement
{
    enum EventEnum {
        EVENT_NULL = 0x00000,
        MOVE_UP = 0x00001,
        MOVE_DOWN = 0x00002,
        MOVE_LEFT = 0x00004,
        MOVE_RIGHT = 0x00008,

        INTERACT = 0x00010,
        ABILITY = 0x00020,
        DEATH_ABILITY = 0x00040,
        DISCONNECT = 0x00080,

        HIGHLIGHT = 0x00100,
        PAUSE = 0x00200,
    };
}

#endif //HIVE_EVENTUTILITIES_H
