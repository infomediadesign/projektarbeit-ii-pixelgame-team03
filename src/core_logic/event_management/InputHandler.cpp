//
// Created by Josi on 07.06.2024.
//

#include "InputHandler.h"
#include "EventUtilities.h"

namespace CoreLogic::EventManagement {

    InputHandler::InputHandler() {

        keyboardDefaultMapping();
        controllerDefaultMapping();

    }



    bool InputHandler::getAxisReleased(Input &pa_axis) {
        return pa_axis.activated;
    }

    bool InputHandler::IsAxisPressed(Input& pa_axis) {
        if (pa_axis.type == Input::AXIS)
        {
            if (pa_axis.direction == Input::AxisDirection::Positive
                && (!pa_axis.activated && GetGamepadAxisMovement(0, pa_axis.axis) < pa_axis.axisThreshold))
            {
                pa_axis.activated = !pa_axis.activated;
                return true;
            } else if (pa_axis.direction == Input::AxisDirection::Negative
                && (!pa_axis.activated && GetGamepadAxisMovement(0, pa_axis.axis) > pa_axis.axisThreshold*-1))
            {
                pa_axis.activated = !pa_axis.activated;
                return true;
            }

        }
        return false;
    }

    bool InputHandler::IsAxisReleased(Input &pa_axis) {
        if (pa_axis.type == Input::AXIS)
        {
            if (pa_axis.direction == Input::AxisDirection::Positive
                && (pa_axis.activated && GetGamepadAxisMovement(0, pa_axis.axis) > pa_axis.axisThreshold))
            {
                pa_axis.activated = !pa_axis.activated;
                return true;
            } else if (pa_axis.direction == Input::AxisDirection::Negative
                       && (pa_axis.activated && GetGamepadAxisMovement(0, pa_axis.axis) < pa_axis.axisThreshold*-1))
            {
                pa_axis.activated = !pa_axis.activated;
                return true;
            }

        }
        return false;
    }


    void InputHandler::keyboardDefaultMapping() {

        keyboardInGameMapping.clear();

        keyboardInGameMapping.insert ({KEY_W, MOVE_UP});
        keyboardInGameMapping.insert ({KEY_S, MOVE_DOWN});
        keyboardInGameMapping.insert ({KEY_A, MOVE_LEFT});
        keyboardInGameMapping.insert ({KEY_D, MOVE_RIGHT});

        keyboardInGameMapping.insert ({KEY_K, INTERACT});
        keyboardInGameMapping.insert ({KEY_J, ABILITY});
        keyboardInGameMapping.insert ({KEY_I, DISCONNECT});
        keyboardInGameMapping.insert ({KEY_L, DEATH_ABILITY});
        keyboardInGameMapping.insert ({KEY_H, HIGHLIGHT});
        keyboardInGameMapping.insert ({KEY_ESCAPE, PAUSE});


//            keyboardMenuMapping.clear();
//
//            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command>, Input> (cursorUpCommand_, KEY_W ));
//            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command>, Input> (cursorLeftCommand_, KEY_A ));
//            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command>, Input> (cursorDownCommand_, KEY_S ));
//            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command>, Input> (cursorRightCommand_, KEY_D ));
//
//            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command>, Input> (selectCommand_, KEY_ENTER ));
//            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command>, Input> (backCommand_, KEY_ESCAPE ));
    }

    void InputHandler::controllerDefaultMapping() {

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

//            controllerMenuMapping.clear();
//
//            controllerMenuMapping.insert({cursorUpCommand_, Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Negative)});
//            controllerMenuMapping.insert({cursorLeftCommand_, Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Negative)});
//            controllerMenuMapping.insert({cursorDownCommand_, Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Positive)});
//            controllerMenuMapping.insert({cursorRightCommand_, Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Positive)});
//
//            controllerMenuMapping.insert({selectCommand_, Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)});
//            controllerMenuMapping.insert({backCommand_, Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)});
    }



    std::vector<EventEnum> InputHandler::handleInput() {
        std::vector<EventEnum> activatedEvents;

        KeyboardKey currentKey = (KeyboardKey) GetKeyPressed();
        GamepadButton currentButton = (GamepadButton) GetGamepadButtonPressed();

        bool keyboardPressed = (currentKey != KEY_NULL);

        //keyboard input
        while (currentKey != KEY_NULL) {
            if (keyboardInGameMapping.find(currentKey) != keyboardInGameMapping.end()) {
                EventEnum event = keyboardInGameMapping.at(currentKey);
                activatedEvents.push_back(event);
            }
            currentKey = (KeyboardKey) GetKeyPressed();
        }
        if (keyboardPressed) {
            return activatedEvents;
        }

        //controller input
        while (currentButton != GAMEPAD_BUTTON_UNKNOWN) {
            if (controllerInGameMapping.find(currentButton) != keyboardInGameMapping.end()) {
                EventEnum event = keyboardInGameMapping.at(currentButton);
                activatedEvents.push_back(event);
            }
            currentButton = (GamepadButton) GetGamepadButtonPressed();
        }
        std::vector<InputHandler::Input> axisInput = GetGamepadAxisPressed();
        for (InputHandler::Input currentAxis : axisInput) {
            if (controllerInGameMapping.find(currentAxis) != keyboardInGameMapping.end()) {
                EventEnum event = keyboardInGameMapping.at(currentAxis);
                activatedEvents.push_back(event);
            }
        }

        return activatedEvents;
    }

    std::vector<InputHandler::Input> InputHandler::GetGamepadAxisPressed() {
        std::vector<InputHandler::Input> axisInput;

        //left stick
        if ((GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > 0.5f)) {
            axisInput.push_back(Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Positive));
        }
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -0.5f) {
            axisInput.push_back(Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Negative));
        }
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > 0.5f) {
            axisInput.push_back(Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Positive));
        }
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -0.5f) {
            axisInput.push_back(Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Negative));
        }

        //right stick
        if ((GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X) > 0.5f)) {
            axisInput.push_back(Input(GAMEPAD_AXIS_RIGHT_X, Input::AxisDirection::Positive));
        }
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X) < -0.5f) {
            axisInput.push_back(Input(GAMEPAD_AXIS_RIGHT_X, Input::AxisDirection::Negative));
        }
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y) > 0.5f) {
            axisInput.push_back(Input(GAMEPAD_AXIS_RIGHT_Y, Input::AxisDirection::Positive));
        }
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y) < -0.5f) {
            axisInput.push_back(Input(GAMEPAD_AXIS_RIGHT_Y, Input::AxisDirection::Negative));
        }

        return axisInput;
    }

    bool InputHandler::isCommandReleased(EventEnum pa_enum) {

        for (auto it : keyboardInGameMapping)
        {
            if (it.second == pa_enum && IsKeyReleased(it.first.key))
            {
                return true;
            }
        }
        for (auto it : controllerInGameMapping) {
            const Input& input = it.first; // "When dealing with a union in a struct, accessing a member of the union can sometimes create a temporary object if the original context does not match the expected type." ~ChatGPT (ich hab kein Plan was genau das heißt aber es funktioniert :])
            if (it.second == pa_enum && (IsGamepadButtonReleased(0, it.first.button) || getAxisReleased((const_cast<Input&>(input))))) {
                return true;
            }
        }
        return false;
    }

}