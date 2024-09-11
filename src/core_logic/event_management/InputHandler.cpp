//
// Created by Josi on 07.06.2024.
//

#include <iostream>
#include "InputHandler.h"
#include "EventUtilities.h"
#include "data_processing/DesignConfig.h"

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
        std::map<Input, EventEnum> controllerMapping;
        std::map<Input, EventEnum> keyboardMapping;

        if (CoreLogic::DataProcessing::StateMachine::getCurrentState() == CoreLogic::DataProcessing::GameState::IN_GAME)
        {
            controllerMapping = controllerInGameMapping_;
            keyboardMapping = keyboardInGameMapping_;
        } else {
            controllerMapping = controllerMenuMapping_;
            keyboardMapping = keyboardMenuMapping_;
        }

        std::vector<EventEnum> activatedEvents;

        KeyboardKey currentKey = (KeyboardKey) GetKeyPressed();
        GamepadButton currentButton = (GamepadButton) GetGamepadButtonPressednotDown();

        bool keyboardPressed = (currentKey != KEY_NULL);

        //keyboard input
        while (currentKey != KEY_NULL)
        {
            if (keyboardMapping.find(currentKey) != keyboardMapping.end())
            {
                EventEnum event = keyboardMapping.at(currentKey);
                activatedEvents.push_back(event);
            }
            currentKey = (KeyboardKey) GetKeyPressed();
        }
        if (keyboardPressed)
        {
            /*for (auto event: activatedEvents)
            {

                std::cout << eventNames::getEventName(event) << ", ";
            }
            std::cout << std::endl;*/
            return activatedEvents;
        }

        //controller input
        if (currentButton != GAMEPAD_BUTTON_UNKNOWN)
        {
            if (controllerMapping.find(currentButton) != controllerMapping.end())
            {
                EventEnum event = controllerMapping.at(currentButton);
                activatedEvents.push_back(event);
            }
        }

        /**
         *  @attention: currently not working; causing crash with vs compiler
         *
        std::vector<InputHandler::Input> axisInput = GetGamepadAxisPressed();
        for (InputHandler::Input currentAxis: axisInput)
        {
            if (controllerMapping.find(currentAxis) != controllerMapping.end())
            {
                EventEnum event = controllerMapping.at(currentAxis);
                activatedEvents.push_back(event);
            }
        }
         */



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
            axisInput.push_back(controllerInGameMapping_.find(input)->first);
        }

        input = Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Negative);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -0.5f)
        {
            updateInputActivated(input, true);
            axisInput.push_back(controllerInGameMapping_.find(input)->first);
        }

        input = Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Positive);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > 0.5f)
        {
            updateInputActivated(input, true);
            axisInput.push_back(controllerInGameMapping_.find(input)->first);
        }

        input = Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Negative);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -0.5f)
        {
            updateInputActivated(input, true);
            axisInput.push_back(controllerInGameMapping_.find(input)->first);
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
        for (auto it: keyboardInGameMapping_)
        {
            if (it.second == pa_enum && IsKeyReleased(it.first.key))
            {
                return true;
            }
        }
        for (auto it: controllerInGameMapping_)
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
        if (controllerInGameMapping_.find(pa_input) != controllerInGameMapping_.end())
        {
            auto it = controllerInGameMapping_.find(pa_input);
            EventEnum event = it->second;
            Input input = pa_input;
            input.activated = pa_activated;
            std::cout << "activated = pa_activated" << std::endl;
            controllerInGameMapping_.erase(it);
            controllerInGameMapping_.insert({input, event});
            if (controllerInGameMapping_.find(input) != controllerInGameMapping_.end())
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
        keyboardInGameMapping_.clear();

        keyboardInGameMapping_.insert({CoreLogic::DataProcessing::DesignConfig::MOVE_UP_KEYBOARD, MOVE_UP});
        keyboardInGameMapping_.insert({CoreLogic::DataProcessing::DesignConfig::MOVE_DOWN_KEYBOARD, MOVE_DOWN});
        keyboardInGameMapping_.insert({CoreLogic::DataProcessing::DesignConfig::MOVE_LEFT_KEYBOARD, MOVE_LEFT});
        keyboardInGameMapping_.insert({CoreLogic::DataProcessing::DesignConfig::MOVE_RIGHT_KEYBOARD, MOVE_RIGHT});

        keyboardInGameMapping_.insert({CoreLogic::DataProcessing::DesignConfig::INTERACT_KEYBOARD, INTERACT});
        keyboardInGameMapping_.insert({CoreLogic::DataProcessing::DesignConfig::ABILITY_KEYBOARD, ABILITY});
        keyboardInGameMapping_.insert({CoreLogic::DataProcessing::DesignConfig::DISCONNECT_KEYBOARD, DISCONNECT});
        keyboardInGameMapping_.insert({CoreLogic::DataProcessing::DesignConfig::DEATH_ABILITY_KEYBOARD, DEATH_ABILITY});



        keyboardMenuMapping_.insert({CoreLogic::DataProcessing::DesignConfig::MOVE_UP_KEYBOARD, MOVE_UP});
        keyboardMenuMapping_.insert({CoreLogic::DataProcessing::DesignConfig::MOVE_DOWN_KEYBOARD, MOVE_DOWN});
        keyboardMenuMapping_.insert({CoreLogic::DataProcessing::DesignConfig::MOVE_LEFT_KEYBOARD, MOVE_LEFT});
        keyboardMenuMapping_.insert({CoreLogic::DataProcessing::DesignConfig::MOVE_RIGHT_KEYBOARD, MOVE_RIGHT});

        keyboardMenuMapping_.insert({CoreLogic::DataProcessing::DesignConfig::MENU_CONFIRM_KEYBOARD, INTERACT});
        keyboardMenuMapping_.insert({CoreLogic::DataProcessing::DesignConfig::MENU_BACK_KEYBOARD, DISCONNECT});
    }

    void InputHandler::controllerDefaultMapping()
    {
        controllerInGameMapping_.clear();

        controllerInGameMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::MOVE_UP_CONTROLLER), MOVE_UP});
        controllerInGameMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::MOVE_DOWN_CONTROLLER), MOVE_DOWN});
        controllerInGameMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::MOVE_LEFT_CONTROLLER), MOVE_LEFT});
        controllerInGameMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::MOVE_RIGHT_CONTROLLER), MOVE_RIGHT});

        controllerInGameMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::INTERACT_CONTROLLER), INTERACT});
        controllerInGameMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::ABILITY_CONTROLLER), ABILITY});
        controllerInGameMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::DISCONNECT_CONTROLLER), DISCONNECT});
        controllerInGameMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::DEATH_ABILITY_CONTROLLER), DEATH_ABILITY});


        controllerMenuMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::MOVE_UP_CONTROLLER), MOVE_UP});
        controllerMenuMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::MOVE_DOWN_CONTROLLER),
                MOVE_DOWN});
        controllerMenuMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::MOVE_LEFT_CONTROLLER),
                MOVE_LEFT});
        controllerMenuMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::MOVE_RIGHT_CONTROLLER),
                MOVE_RIGHT});

        controllerMenuMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::MENU_CONFIRM_CONTROLLER), INTERACT});
        controllerMenuMapping_.insert({Input(CoreLogic::DataProcessing::DesignConfig::MENU_BACK_CONTROLLER),
                DISCONNECT});
    }



}
