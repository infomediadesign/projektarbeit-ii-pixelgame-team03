//
// Created by Josi on 07.06.2024.
//

#include <iostream>
#include "InputHandler.h"
#include "EventUtilities.h"

namespace CoreLogic::EventManagement
{

    InputHandler::InputHandler()
    {
        keyboardDefaultMapping();
        controllerDefaultMapping();
    }


    bool InputHandler::IsAxisPressed(Input &pa_axis)
    {
        if (pa_axis.type == Input::AXIS)
        {
            if (pa_axis.direction == Input::AxisDirection::Positive
                && (!pa_axis.activated && GetGamepadAxisMovement(0, pa_axis.axis) < pa_axis.axisThreshold))
            {
                updateInputActivated(pa_axis, true);
                return true;
            } else if (pa_axis.direction == Input::AxisDirection::Negative
                       && (!pa_axis.activated && GetGamepadAxisMovement(0, pa_axis.axis) > pa_axis.axisThreshold * -1))
            {
                updateInputActivated(pa_axis, true);
                return true;
            }

        }
        return false;
    }

    bool InputHandler::IsAxisReleased(Input &pa_axis)
    {
        std::cout << pa_axis.activated << std::endl;

        if (pa_axis.type == Input::AXIS)
        {
            if (pa_axis.direction == Input::AxisDirection::Positive
                && (pa_axis.activated && GetGamepadAxisMovement(0, pa_axis.axis) > pa_axis.axisThreshold))
            {
                updateInputActivated(pa_axis, false);
                return true;
            } else if (pa_axis.direction == Input::AxisDirection::Negative
                       && (pa_axis.activated && GetGamepadAxisMovement(0, pa_axis.axis) < pa_axis.axisThreshold * -1))
            {
                updateInputActivated(pa_axis, false);
                return true;
            }

        }
        return false;
    }


    void InputHandler::keyboardDefaultMapping()
    {
        keyboardInGameMapping.clear();

        keyboardInGameMapping.insert({KEY_W, MOVE_UP});
        keyboardInGameMapping.insert({KEY_S, MOVE_DOWN});
        keyboardInGameMapping.insert({KEY_A, MOVE_LEFT});
        keyboardInGameMapping.insert({KEY_D, MOVE_RIGHT});

        keyboardInGameMapping.insert({KEY_K, INTERACT});
        keyboardInGameMapping.insert({KEY_J, ABILITY});
        keyboardInGameMapping.insert({KEY_I, DISCONNECT});
        keyboardInGameMapping.insert({KEY_L, DEATH_ABILITY});
        keyboardInGameMapping.insert({KEY_H, HIGHLIGHT});
        keyboardInGameMapping.insert({KEY_ESCAPE, PAUSE});
    }

    void InputHandler::controllerDefaultMapping()
    {

        controllerInGameMapping.clear();

        controllerInGameMapping.insert({Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Negative), MOVE_UP});
        controllerInGameMapping.insert({Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Negative), MOVE_LEFT});
        controllerInGameMapping.insert({Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Positive), MOVE_DOWN});
        controllerInGameMapping.insert({Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Positive), MOVE_RIGHT});

        controllerInGameMapping.insert({Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN), INTERACT});
        controllerInGameMapping.insert({Input(GAMEPAD_BUTTON_RIGHT_TRIGGER_1), ABILITY});
        controllerInGameMapping.insert({Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN), DISCONNECT});
        controllerInGameMapping.insert({Input(GAMEPAD_BUTTON_RIGHT_TRIGGER_2), DEATH_ABILITY});
        controllerInGameMapping.insert({Input(GAMEPAD_BUTTON_LEFT_TRIGGER_1), HIGHLIGHT});
        controllerInGameMapping.insert({Input(GAMEPAD_BUTTON_MIDDLE_RIGHT), PAUSE});
    }


    std::vector<EventEnum> InputHandler::handleInput()
    {
        std::vector<EventEnum> activatedEvents;

        KeyboardKey currentKey = (KeyboardKey) GetKeyPressed();
        GamepadButton currentButton = (GamepadButton) GetGamepadButtonPressed();

        bool keyboardPressed = (currentKey != KEY_NULL);

        //keyboard input
        while (currentKey != KEY_NULL)
        {
            if (keyboardInGameMapping.find(currentKey) != keyboardInGameMapping.end())
            {
                EventEnum event = keyboardInGameMapping.at(currentKey);
                activatedEvents.push_back(event);
            }
            currentKey = (KeyboardKey) GetKeyPressed();
        }
        if (keyboardPressed)
        {
            return activatedEvents;
        }

        //controller input
        while (currentButton != GAMEPAD_BUTTON_UNKNOWN)
        {
            if (controllerInGameMapping.find(currentButton) != controllerInGameMapping.end())
            {
                EventEnum event = controllerInGameMapping.at(currentButton);
                activatedEvents.push_back(event);
            }
            currentButton = (GamepadButton) GetGamepadButtonPressed();
        }

        std::vector<InputHandler::Input> axisInput = GetGamepadAxisPressed();
        for (InputHandler::Input currentAxis: axisInput)
        {
            if (controllerInGameMapping.find(currentAxis) != controllerInGameMapping.end())
            {
                EventEnum event = controllerInGameMapping.at(currentAxis);
                activatedEvents.push_back(event);

//                std::cout << controllerInGameMapping.find(currentAxis)->first.activated << std::endl;
//                updateInputActivated(currentAxis, true);
//                std::cout << controllerInGameMapping.find(currentAxis)->first.activated << std::endl;

            }
        }

        return activatedEvents;
    }

    std::vector<InputHandler::Input> InputHandler::GetGamepadAxisPressed()
    {
        std::vector<InputHandler::Input> axisInput;

        //left stick
        Input input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Positive);
        if ((GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > 0.5f))
        {
            axisInput.push_back(input);
        }

        input = Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Negative);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -0.5f)
        {
            axisInput.push_back(input);
        }

        input = Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Positive);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > 0.5f)
        {
            axisInput.push_back(input);
        }

        input = Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Negative);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -0.5f)
        {
            axisInput.push_back(input);
        }

        //right stick
        if ((GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X) > 0.5f))
        {
            axisInput.push_back(Input(GAMEPAD_AXIS_RIGHT_X, Input::AxisDirection::Positive));
        }

        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X) < -0.5f)
        {
            axisInput.push_back(Input(GAMEPAD_AXIS_RIGHT_X, Input::AxisDirection::Negative));
        }

        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y) > 0.5f)
        {
            axisInput.push_back(Input(GAMEPAD_AXIS_RIGHT_Y, Input::AxisDirection::Positive));
        }

        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y) < -0.5f)
        {
            axisInput.push_back(Input(GAMEPAD_AXIS_RIGHT_Y, Input::AxisDirection::Negative));
        }

        return axisInput;
    }

    bool InputHandler::isCommandReleased(EventEnum pa_enum)
    {
//        std::cout << "\n"
//                     "\n"
//                     "isCommandReleased: " << pa_enum << std::endl;

        for (auto it: keyboardInGameMapping)
        {
//            std::cout << "Keyboard:" << it.second << std::endl;
            if (it.second == pa_enum && IsKeyReleased(it.first.key))
            {
//                std::cout << "return true" << std::endl;
                return true;
            }
        }
        for (auto it: controllerInGameMapping)
        {
            const Input &input = it.first; // "When dealing with a union in a struct, accessing a member of the union can sometimes create a temporary object if the original context does not match the expected type." ~ChatGPT (ich hab kein Plan was genau das heißt aber es funktioniert :])

            if (it.second == pa_enum &&
                (IsGamepadButtonReleased(0, it.first.button) || IsAxisReleased((const_cast<Input &>(input)))))
            {
                std::cout << "return true" << std::endl;
                return true;
            }
        }
        return false;
    }

    void InputHandler::updateInputActivated(InputHandler::Input &pa_input, bool pa_activated)
    {
        if (controllerInGameMapping.find(pa_input) != controllerInGameMapping.end())
        {
            auto it = controllerInGameMapping.find(pa_input);
            EventEnum event = it->second;
            Input input = pa_input;
            input.activated = pa_activated;
            controllerInGameMapping.erase(it);
            controllerInGameMapping.insert({input, event});
        }
    }
}