//
// Created by Josi on 07.06.2024.
//

#ifndef HIVE_INPUTHANDLER_H
#define HIVE_INPUTHANDLER_H

#include <raylib.h>
#include <memory>
#include <map>
#include <vector>

enum EventEnum {
    EVENT_NULL,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,

    INTERACT,
    ABILITY,
    DEATH_ABILITY,
    DISCONNECT,

    HIGHLIGHT,
    PAUSE,
};

namespace CoreLogic::EventManagement {

        class InputHandler {
            struct Input {
                enum Type {
                    BUTTON,
                    AXIS,
                    KEYBOARD
                } type;

                union {
                    GamepadButton button;
                    GamepadAxis axis;
                    KeyboardKey key;
                };

                enum AxisDirection {
                    Positive,
                    Negative
                } direction;

                float axisThreshold = 0.5f;
                bool activated = false;

                Input(GamepadButton btn) : type(BUTTON), button(btn) {}
                Input(GamepadAxis ax, AxisDirection dir) : type(AXIS), axis(ax), direction(dir) {}
                Input(KeyboardKey k) : type(KEYBOARD), key(k) {}

                bool operator==(const Input &other) const {
                    if (type != other.type) return false;
                    if (type == BUTTON) return button == other.button;
                    if (type == AXIS) return axis == other.axis && direction == other.direction;
                    if (type == KEYBOARD) return key == other.key;
                }

                bool operator<(const Input &other) const {
                    if (type != other.type) return type < other.type;
                    if (type == BUTTON) return button < other.button;
                    if (type == AXIS) {
                        if (axis != other.axis) return axis < other.axis;
                        return direction < other.direction;
                    }
                    if (type == KEYBOARD) return key < other.key;
                    return false;
                }
            };



            public:
                InputHandler();

                bool isAxisPressed(Input& pa_axis);
                bool isAxisReleased(Input& pa_axis);
                std::vector<Input> GetGamepadAxisPressed();

                void keyboardDefaultMapping();
                void controllerDefaultMapping();

                std::vector<EventEnum> handleInput();

                //void testRemap();

    //            void remap(std::map<std::shared_ptr<Command>, Input> &pa_map,
    //                       const std::shared_ptr<Command> &pa_Command, Input pa_newInput);


                //Input detection
                //KeyboardKey detectKeyboardInput();

            protected:
                std::map<Input, EventEnum> keyboardInGameMapping;
                //std::map<std::shared_ptr<Command>, Input> keyboardMenuMapping;

                std::map<Input, EventEnum> controllerInGameMapping;
                //std::map<std::shared_ptr<Command>, Input> controllerMenuMapping;

        };

}

#endif //HIVE_INPUTHANDLER_H
