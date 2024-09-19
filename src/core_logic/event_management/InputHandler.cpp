//
// Created by Josi on 07.06.2024.
//

#include <iostream>
#include "InputHandler.h"
#include "EventUtilities.h"
#include "data_processing/DesignConfig.h"

bool CoreLogic::EventManagement::InputHandler::lastInputKeyBoard_ = true;
std::mutex CoreLogic::EventManagement::InputHandler::inputHandler_mutex_;


CoreLogic::EventManagement::InputHandler &CoreLogic::EventManagement::InputHandler::getInstance()
{
    static CoreLogic::EventManagement::InputHandler instance;
    return instance;
}

namespace CoreLogic::EventManagement
{

    InputHandler::InputHandler()
    {
        keyboardInGameMapping_ = std::make_shared<std::map<EventEnum, std::shared_ptr<Input>>>();
        controllerInGameMapping_ = std::make_shared<std::map<EventEnum, std::shared_ptr<Input>>>();

        keyboardMenuMapping_ = std::make_shared<std::map<EventEnum, std::shared_ptr<Input>>>();
        controllerMenuMapping_ = std::make_shared<std::map<EventEnum, std::shared_ptr<Input>>>();

        keyboardDefaultMapping();
        controllerDefaultMapping();
    }


    std::vector<EventEnum> InputHandler::handleInput()
    {

        std::shared_ptr<std::map<EventEnum, std::shared_ptr<Input>>> controllerMapping;
        std::shared_ptr<std::map<EventEnum, std::shared_ptr<Input>>> keyboardMapping;

        if (CoreLogic::DataProcessing::StateMachine::getCurrentState() == CoreLogic::DataProcessing::GameState::IN_GAME)
        {
            controllerMapping = controllerInGameMapping_;
            keyboardMapping = keyboardInGameMapping_;
        } else {
            controllerMapping = controllerMenuMapping_;
            keyboardMapping = keyboardMenuMapping_;
        }

        std::vector<EventEnum> activatedEvents;

        GamepadButton currentButton = (GamepadButton) GetGamepadButtonPressednotDown();

        bool keyboardPressed = false;

        //keyboard input
        for (auto pair : *keyboardMapping)
        {
            if (IsKeyPressed((KeyboardKey) *pair.second))
            {
                activatedEvents.push_back(pair.first);
                keyboardPressed = true;
            }
        }
        if (keyboardPressed)
        {
            lastInputKeyBoard_ = true;
            return activatedEvents;
        }

        //controller input
        for (auto pair : *controllerMapping)
        {
            if (pair.second->type == Input::BUTTON)
            {
                if (IsGamepadButtonPressed(0, (GamepadButton) *pair.second))
                {
                    activatedEvents.push_back(pair.first);
                    lastInputKeyBoard_ = false;
                }
            } else if (pair.second->type == Input::AXIS)
            {
                if (IsGamepadAxisPressed(pair.second))
                {
                    activatedEvents.push_back(pair.first);
                    pair.second->activated = true;
                    lastInputKeyBoard_ = false;
                } else {
                    pair.second->activated = false;
                }
            }
        }

        return activatedEvents;
    }

    bool InputHandler::isCommandReleased(EventEnum pa_enum)
    {
        for (auto pair: *keyboardInGameMapping_)
        {
            if (pair.first == pa_enum && IsKeyReleased(pair.second->key))
            {
                return true;
            }
        }
        for (auto pair: *controllerInGameMapping_)
        {

            if (pair.first == pa_enum )
            {
            if (pair.second->type == Input::BUTTON && IsGamepadButtonReleased(0, pair.second->button))
            {
                return true;
            } else if (pair.second->type == Input::AXIS && IsGamepadAxisReleased(pair.second))
            {
                return true;
            }
            }
        }
        return false;
    }

    bool InputHandler::isCommandDown(EventEnum pa_enum)
    {
        for (auto pair: *keyboardInGameMapping_)
        {
            if (pair.first == pa_enum && IsKeyDown(pair.second->key))
            {
                return true;
            }
        }
        for (auto pair: *controllerInGameMapping_)
        {

            if (pair.first == pa_enum )
            {
                if (pair.second->type == Input::BUTTON && IsGamepadButtonDown(0, pair.second->button))
                {
                    return true;
                } else if (pair.second->type == Input::AXIS && IsGamepadAxisDown(pair.second))
                {
                    return true;
                }
            }
        }
        return false;
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
        keyboardInGameMapping_->clear();

        keyboardInGameMapping_->insert({MOVE_UP, std::make_shared<Input>(KEY_W)});
        keyboardInGameMapping_->insert({MOVE_DOWN, std::make_shared<Input>(KEY_S)});
        keyboardInGameMapping_->insert({MOVE_LEFT, std::make_shared<Input>(KEY_A)});
        keyboardInGameMapping_->insert({MOVE_RIGHT, std::make_shared<Input>(KEY_D)});

        keyboardInGameMapping_->insert({INTERACT, std::make_shared<Input>(CoreLogic::DataProcessing::DesignConfig::INTERACT_KEYBOARD)});
        keyboardInGameMapping_->insert({ABILITY, std::make_shared<Input>(CoreLogic::DataProcessing::DesignConfig::ABILITY_KEYBOARD)});
//        keyboardInGameMapping_->insert({DISCONNECT, std::make_shared<Input>(CoreLogic::DataProcessing::DesignConfig::DISCONNECT_KEYBOARD)});
        keyboardInGameMapping_->insert({DEATH_ABILITY, std::make_shared<Input>(CoreLogic::DataProcessing::DesignConfig::DEATH_ABILITY_KEYBOARD)});
        keyboardInGameMapping_->insert({HUD_TOGGLE, std::make_shared<Input>(CoreLogic::DataProcessing::DesignConfig::DISCONNECT_KEYBOARD)});


        keyboardMenuMapping_->clear();

        keyboardMenuMapping_->insert({MOVE_UP, std::make_shared<Input>(KEY_W)});
        keyboardMenuMapping_->insert({MOVE_DOWN, std::make_shared<Input>(KEY_S)});
        keyboardMenuMapping_->insert({MOVE_LEFT, std::make_shared<Input>(KEY_A)});
        keyboardMenuMapping_->insert({MOVE_RIGHT, std::make_shared<Input>(KEY_D)});

        keyboardMenuMapping_->insert({ENTER, std::make_shared<Input>
                (CoreLogic::DataProcessing::DesignConfig::MENU_CONFIRM_KEYBOARD)});

    }

    void InputHandler::controllerDefaultMapping()
    {
        controllerInGameMapping_->clear();

        controllerInGameMapping_->insert({MOVE_UP, std::make_shared<Input>(GAMEPAD_AXIS_LEFT_Y, Input::NEGATIVE)});
        controllerInGameMapping_->insert({MOVE_DOWN, std::make_shared<Input>(GAMEPAD_AXIS_LEFT_Y, Input::POSITIVE)});
        controllerInGameMapping_->insert({MOVE_LEFT, std::make_shared<Input>(GAMEPAD_AXIS_LEFT_X, Input::NEGATIVE)});
        controllerInGameMapping_->insert({MOVE_RIGHT, std::make_shared<Input>(GAMEPAD_AXIS_LEFT_X, Input::POSITIVE)});

        controllerInGameMapping_->insert({INTERACT, std::make_shared<Input>(CoreLogic::DataProcessing::DesignConfig::INTERACT_CONTROLLER)});
        controllerInGameMapping_->insert({ABILITY, std::make_shared<Input>(CoreLogic::DataProcessing::DesignConfig::ABILITY_CONTROLLER)});
        // controllerInGameMapping_->insert({DISCONNECT, std::make_shared<Input>(CoreLogic::DataProcessing::DesignConfig::DISCONNECT_CONTROLLER)});
        controllerInGameMapping_->insert({DEATH_ABILITY, std::make_shared<Input>(CoreLogic::DataProcessing::DesignConfig::DEATH_ABILITY_CONTROLLER)});
        controllerInGameMapping_->insert({HUD_TOGGLE, std::make_shared<Input>(CoreLogic::DataProcessing::DesignConfig::DISCONNECT_CONTROLLER)});


        controllerMenuMapping_->clear();

        controllerMenuMapping_->insert({MOVE_UP, std::make_shared<Input>(GAMEPAD_AXIS_LEFT_Y, Input::NEGATIVE)});
        controllerMenuMapping_->insert({MOVE_DOWN, std::make_shared<Input>(GAMEPAD_AXIS_LEFT_Y, Input::POSITIVE)});
        controllerMenuMapping_->insert({MOVE_LEFT, std::make_shared<Input>(GAMEPAD_AXIS_LEFT_X, Input::NEGATIVE)});
        controllerMenuMapping_->insert({MOVE_RIGHT, std::make_shared<Input>(GAMEPAD_AXIS_LEFT_X, Input::POSITIVE)});

        controllerMenuMapping_->insert({ENTER, std::make_shared<Input>
                (CoreLogic::DataProcessing::DesignConfig::MENU_CONFIRM_CONTROLLER)});

    }

    bool InputHandler::gatLastInputKeyboard()
    {
        return lastInputKeyBoard_;
    }

    bool InputHandler::IsGamepadAxisPressed(std::shared_ptr<Input> pa_axis)
    {
        if ((!pa_axis->activated))
            if (pa_axis->direction == Input::AxisDirection::POSITIVE
                && GetGamepadAxisMovement(0, (GamepadAxis) *pa_axis) >
                    CoreLogic::DataProcessing::DesignConfig::AXIS_THRESHOLD)
            {
                pa_axis->activated = true;
                return true;
            } else if (pa_axis->direction == Input::AxisDirection::NEGATIVE
                && GetGamepadAxisMovement(0,(GamepadAxis) *pa_axis) <
                    CoreLogic::DataProcessing::DesignConfig::AXIS_THRESHOLD * -1)
            {
                pa_axis->activated = true;
                return true;
            }
        return false;
    }

    bool InputHandler::IsGamepadAxisReleased(std::shared_ptr<Input> pa_axis)
    {
        if ((pa_axis->activated))
            if (pa_axis->direction == Input::AxisDirection::POSITIVE
                    && GetGamepadAxisMovement(0, (GamepadAxis) *pa_axis) <=
                    CoreLogic::DataProcessing::DesignConfig::AXIS_THRESHOLD)
            {
                pa_axis->activated = false;
                return true;
            } else if (pa_axis->direction == Input::AxisDirection::NEGATIVE
            && GetGamepadAxisMovement(0, (GamepadAxis) *pa_axis) >=
                    CoreLogic::DataProcessing::DesignConfig::AXIS_THRESHOLD * -1)
            {
                pa_axis->activated = false;
                return true;
            }
        return false;
    }

    bool InputHandler::IsGamepadAxisDown(std::shared_ptr<Input> pa_axis)
    {
        if (pa_axis->direction == Input::AxisDirection::POSITIVE
                && GetGamepadAxisMovement(0, (GamepadAxis) *pa_axis) >
                CoreLogic::DataProcessing::DesignConfig::AXIS_THRESHOLD)
        {
            pa_axis->activated = true;
            return true;
        } else if (pa_axis->direction == Input::AxisDirection::NEGATIVE
                && GetGamepadAxisMovement(0,(GamepadAxis) *pa_axis) <
                CoreLogic::DataProcessing::DesignConfig::AXIS_THRESHOLD * -1)
        {
            pa_axis->activated = true;
            return true;
        }
        return false;
    }


}
