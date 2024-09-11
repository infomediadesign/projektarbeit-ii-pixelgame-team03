//
// Created by Josi on 07.06.2024.
//

#ifndef HIVE_INPUTHANDLER_H
#define HIVE_INPUTHANDLER_H

#include <raylib.h>
#include <memory>
#include <map>
#include <vector>
#include "EventUtilities.h"
#include "data_processing/Store.h"


namespace CoreLogic::EventManagement {

        class InputHandler
        {
            struct Input
            {
                enum Type
                {
                    BUTTON, AXIS, KEYBOARD
                } type;

                union
                {
                    GamepadButton button;
                    GamepadAxis axis;
                    KeyboardKey key;
                };

                enum AxisDirection
                {
                    Positive, Negative
                } direction;

                float axisThreshold = 0.5f;
                bool activated = false;

                Input(GamepadButton btn) :
                        type(BUTTON), button(btn)
                {
                }

                Input(GamepadAxis ax, AxisDirection dir) :
                        type(AXIS), axis(ax), direction(dir)
                {
                }

                Input(KeyboardKey k) :
                        type(KEYBOARD), key(k)
                {
                }

                bool operator==(const Input &other) const
                {
                    if (type != other.type)
                        return false;
                    if (type == BUTTON)
                        return button == other.button;
                    if (type == AXIS)
                        return axis == other.axis && direction == other.direction;
                    if (type == KEYBOARD)
                        return key == other.key;
                }

                bool operator<(const Input &other) const
                {
                    if (type != other.type)
                        return type < other.type;
                    if (type == BUTTON)
                        return button < other.button;
                    if (type == AXIS)
                    {
                        if (axis != other.axis)
                            return axis < other.axis;
                        return direction < other.direction;
                    }
                    if (type == KEYBOARD)
                        return key < other.key;
                    return false;
                }
            };

        public:
            InputHandler();

            bool IsAxisPressed(Input &pa_axis);

            bool IsAxisReleased(Input &pa_axis);

            bool getAxisReleased(Input &pa_axis);

            std::vector<Input> GetGamepadAxisPressed();

            GamepadButton GetGamepadButtonPressednotDown();

            void keyboardDefaultMapping();

            void controllerDefaultMapping();

            std::vector<EventEnum> handleInput();

            bool isCommandReleased(EventEnum pa_enum);
            bool isCommandUp(EventEnum pa_enum);


        protected:
            std::map<Input, EventEnum> keyboardInGameMapping_;
            std::map<Input, EventEnum> controllerInGameMapping_;


            std::map<Input, EventEnum> keyboardMenuMapping_;
            std::map<Input, EventEnum> controllerMenuMapping_;

            void updateInputActivated(Input &pa_input, bool pa_activated);

            GamepadButton lastPressedButton = GAMEPAD_BUTTON_UNKNOWN;

        };

}

#endif //HIVE_INPUTHANDLER_H