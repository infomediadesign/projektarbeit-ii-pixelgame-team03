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
        public:
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
                    POSITIVE, NEGATIVE
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

                operator KeyboardKey() const
                {
                    if (type == KEYBOARD)
                    {
                        return key;
                    }
                    throw std::bad_cast();
                }

                operator GamepadButton () const
                {
                    if (type == BUTTON)
                    {
                        return button;
                    }
                    throw std::bad_cast();
                }

                operator GamepadAxis () const
                {
                    if (type == AXIS)
                    {
                        return axis;
                    }
                    throw std::bad_cast();
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

            InputHandler();
            static InputHandler &getInstance();

            static bool gatLastInputKeyboard();

            bool IsGamepadAxisPressed(std::shared_ptr<Input> pa_axis);
            bool IsGamepadAxisDown(std::shared_ptr<Input> pa_axis);
            bool IsGamepadAxisReleased(std::shared_ptr<Input> pa_axis);

            GamepadButton GetGamepadButtonPressednotDown();

            void keyboardDefaultMapping();

            void controllerDefaultMapping();

            std::vector<EventEnum> handleInput();

            bool isCommandReleased(EventEnum pa_enum);
            bool isCommandDown(EventEnum pa_enum);


        protected:
            static std::mutex inputHandler_mutex_;

            std::shared_ptr<std::map<EventEnum, std::shared_ptr<Input>>> keyboardInGameMapping_;
            std::shared_ptr<std::map<EventEnum, std::shared_ptr<Input>>> controllerInGameMapping_;


            std::shared_ptr<std::map<EventEnum, std::shared_ptr<Input>>> keyboardMenuMapping_;
            std::shared_ptr<std::map<EventEnum, std::shared_ptr<Input>>> controllerMenuMapping_;

            GamepadButton lastPressedButton = GAMEPAD_BUTTON_UNKNOWN;

            static bool lastInputKeyBoard_;

        };

}

#endif //HIVE_INPUTHANDLER_H