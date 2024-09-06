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

        ABILITY,
        CLEAN,
        PUSH,
        BARREL,
        JUMP,
        FALLING,

        DEATH_ABILITY,
        DISCONNECT,

        VISION,

        HIGHLIGHT,
        PAUSE
    };
}

#endif //HIVE_EVENTUTILITIES_H
