//
// Created by Josi on 07.06.2024.
//

#include <iostream>
#include "InputHandler.h"
#include "EventUtilities.h"
#include "../data_processing/DesignConfig.h"

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
        if (pa_axis.type == Input::AXIS)
        {
            if (pa_axis.direction == Input::AxisDirection::Positive)
            {
                if (pa_axis.activated)
                {
                    if (GetGamepadAxisMovement(0, pa_axis.axis) > pa_axis.axisThreshold)
                    {
                        updateInputActivated(pa_axis, false);
                        return true;
                    }
                }
            }else if (pa_axis.direction == Input::AxisDirection::Negative)
            {
                if (pa_axis.activated && GetGamepadAxisMovement(0, pa_axis.axis) < pa_axis.axisThreshold * -1)
                {
                    updateInputActivated(pa_axis, false);
                    return true;
                }
            }

        }
        return false;
    }


    std::vector<EventEnum> InputHandler::handleInput()
    {
        std::vector<EventEnum> activatedEvents;

        KeyboardKey currentKey = (KeyboardKey) GetKeyPressed();
        GamepadButton currentButton = (GamepadButton) GetGamepadButtonPressednotDown();

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
        if (currentButton != GAMEPAD_BUTTON_UNKNOWN)
        {
            if (controllerInGameMapping.find(currentButton) != controllerInGameMapping.end())
            {
                EventEnum event = controllerInGameMapping.at(currentButton);
                activatedEvents.push_back(event);
            }
        }

        std::vector<InputHandler::Input> axisInput = GetGamepadAxisPressed();
        for (InputHandler::Input currentAxis: axisInput)
        {
            if (controllerInGameMapping.find(currentAxis) != controllerInGameMapping.end())
            {
                EventEnum event = controllerInGameMapping.at(currentAxis);
                activatedEvents.push_back(event);
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
            updateInputActivated(input, true);
            axisInput.push_back(controllerInGameMapping.find(input)->first);
        }

        input = Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Negative);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -0.5f)
        {
            updateInputActivated(input, true);
            axisInput.push_back(controllerInGameMapping.find(input)->first);
        }

        input = Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Positive);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > 0.5f)
        {
            updateInputActivated(input, true);
            axisInput.push_back(controllerInGameMapping.find(input)->first);
        }

        input = Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Negative);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -0.5f)
        {
            updateInputActivated(input, true);
            axisInput.push_back(controllerInGameMapping.find(input)->first);
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
        for (auto it: keyboardInGameMapping)
        {
            if (it.second == pa_enum && IsKeyReleased(it.first.key))
            {
                return true;
            }
        }
        for (auto it: controllerInGameMapping)
        {
            Input& input = const_cast<Input &>(it.first); // "When dealing with a union in a struct, accessing a member of the union can sometimes create a temporary object if the original context does not match the expected type." ~ChatGPT (ich hab kein Plan was genau das heißt aber es funktioniert :])

            if (it.second == pa_enum &&
                (IsGamepadButtonReleased(0, it.first.button) || IsAxisReleased(input)))
            {
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
            std::cout << "activated = pa_activated" << std::endl;
            controllerInGameMapping.erase(it);
            controllerInGameMapping.insert({input, event});
            if (controllerInGameMapping.find(input) != controllerInGameMapping.end())
            {
                std::cout << "Input found" << std::endl;
            }
        }
    }

    GamepadButton InputHandler::GetGamepadButtonPressednotDown()
    {
        GamepadButton currentButton = (GamepadButton) GetGamepadButtonPressed();

        if (currentButton == lastPressedButton)
        {
            currentButton = GAMEPAD_BUTTON_UNKNOWN;
        } else {
            lastPressedButton = currentButton;
        }
        return currentButton;
    }

    void InputHandler::keyboardDefaultMapping()
    {
        keyboardInGameMapping.clear();

        keyboardInGameMapping.insert({CoreLogic::DataProcessing::DesignConfig::MOVE_UP_KEYBOARD, MOVE_UP});
        keyboardInGameMapping.insert({CoreLogic::DataProcessing::DesignConfig::MOVE_DOWN_KEYBOARD, MOVE_DOWN});
        keyboardInGameMapping.insert({CoreLogic::DataProcessing::DesignConfig::MOVE_LEFT_KEYBOARD, MOVE_LEFT});
        keyboardInGameMapping.insert({CoreLogic::DataProcessing::DesignConfig::MOVE_RIGHT_KEYBOARD, MOVE_RIGHT});

        keyboardInGameMapping.insert({CoreLogic::DataProcessing::DesignConfig::INTERACT_KEYBOARD, INTERACT});
        keyboardInGameMapping.insert({CoreLogic::DataProcessing::DesignConfig::ABILITY_KEYBOARD, ABILITY});
        keyboardInGameMapping.insert({CoreLogic::DataProcessing::DesignConfig::DISCONNECT_KEYBOARD, DISCONNECT});
        keyboardInGameMapping.insert({CoreLogic::DataProcessing::DesignConfig::DEATH_ABILITY_KEYBOARD, DEATH_ABILITY});
    }

    void InputHandler::controllerDefaultMapping()
    {
        controllerInGameMapping.clear();

        controllerInGameMapping.insert({Input(CoreLogic::DataProcessing::DesignConfig::MOVE_UP_CONTROLLER), MOVE_UP});
        controllerInGameMapping.insert({Input(CoreLogic::DataProcessing::DesignConfig::MOVE_DOWN_CONTROLLER), MOVE_DOWN});
        controllerInGameMapping.insert({Input(CoreLogic::DataProcessing::DesignConfig::MOVE_LEFT_CONTROLLER), MOVE_LEFT});
        controllerInGameMapping.insert({Input(CoreLogic::DataProcessing::DesignConfig::MOVE_RIGHT_CONTROLLER), MOVE_RIGHT});

        controllerInGameMapping.insert({Input(CoreLogic::DataProcessing::DesignConfig::INTERACT_CONTROLLER), INTERACT});
        controllerInGameMapping.insert({Input(CoreLogic::DataProcessing::DesignConfig::ABILITY_CONTROLLER), ABILITY});
        controllerInGameMapping.insert({Input(CoreLogic::DataProcessing::DesignConfig::DISCONNECT_CONTROLLER), DISCONNECT});
        controllerInGameMapping.insert({Input(CoreLogic::DataProcessing::DesignConfig::DEATH_ABILITY_CONTROLLER), DEATH_ABILITY});
    }


}
