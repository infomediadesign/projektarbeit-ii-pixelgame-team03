//
// Created by keanu on 6/18/2024.
//

#ifndef HIVE_EVENTUTILITIES_H
#define HIVE_EVENTUTILITIES_H

namespace CoreLogic::EventManagement
{
    class EventException : public std::exception {
    public:
        explicit EventException(const char* pa_message, bool pa_success) : msg_(pa_message), success_(pa_success) {}

        [[nodiscard]] bool wasSuccessful() const { return success_; }

        [[nodiscard]] const char* what() const noexcept override { return msg_; }

    private:
        const char* msg_;
        bool success_ = true;
    };

    enum EventEnum {
        EVENT_NULL,
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,

        INTERACT,
        CLIMB,
        CHECKPOINT,
        NOTE,

        ABILITY,
        CLEAN,
        PUSH,
        BARREL_PUSH,
        JUMP,

        FALLING,
        BOULDER_FALL,
        BARREL_FALL,

        DEATH_ABILITY,
        DISCONNECT,
        ENEMY_DEATH,

        VISION,

        HIGHLIGHT,
        PAUSE,
        ENTER,

        HUD_TOGGLE,
    };

    struct eventNames {
    public:
        static std::string getEventName(EventEnum pa_event)
        {
            return eventNameMap[pa_event];
        }
    private:
        static std::map<EventEnum, std::string> eventNameMap;
    };


}

#endif //HIVE_EVENTUTILITIES_H
