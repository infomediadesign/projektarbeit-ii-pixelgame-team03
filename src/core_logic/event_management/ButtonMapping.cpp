//
// Created by Josi on 07.06.2024.
//

#include "ButtonMapping.h"
#include <iostream>

namespace CoreLogic {
    namespace EventManagement {


        void ButtonMapping::remap(std::map<std::shared_ptr<Command>, Input>& pa_map, const std::shared_ptr<Command>& pa_Command, Input pa_newKey) {

            KeyboardKey newKey;
            while (detectKeyboardInput() != KEY_NULL) {
                std::cout << "clearing previous key" << std::endl;

            }
            std::cout << "cleared previous key" << std::endl;
            while (IsKeyDown(KEY_NULL)) {
                std::cout << "new key" << std::endl;
            }

            //find Command & check if key is already in use
            auto CommandIterator = pa_map.find(pa_Command);
            for(std::pair<const std::shared_ptr<Command>, Input> CommandPair : pa_map) {
                if (CommandPair.second == newKey) {
                    std::cout << "Key already in use. Swapping Keys." << std::endl;

                    //save the old Command and the keybind to swap (currend keybind of the Command that is supposed to be rebound)
                    auto usedCommand = CommandPair.first;
                    auto usedCommandIterator = pa_map.find(usedCommand);
                    auto swappedKey = CommandIterator->second;

                    //erase and insert old Command with swapped key
                    pa_map.erase(usedCommandIterator);
                    pa_map.insert(std::pair<std::shared_ptr<Command>, Input>(usedCommand, swappedKey));
                    break;
                }
            }

            //insert new Command
            pa_map.erase(CommandIterator);
            pa_map.insert(std::pair<std::shared_ptr<Command>, Input>(pa_Command, newKey));
        }


        void ButtonMapping::checkKeyboardMovement() {
            executeIfPressed(keyboardInGameMapping, moveUpCommand_);
            executeIfPressed(keyboardInGameMapping, moveDownCommand_);
            executeIfPressed(keyboardInGameMapping, moveLeftCommand_);
            executeIfPressed(keyboardInGameMapping, moveRightCommand_);
        }

        void ButtonMapping::checkControllerMovement() {
            executeIfPressed(controllerInGameMapping, moveUpCommand_);
            executeIfPressed(controllerInGameMapping, moveDownCommand_);
            executeIfPressed(controllerInGameMapping, moveLeftCommand_);
            executeIfPressed(controllerInGameMapping, moveRightCommand_);
        }

        void ButtonMapping::executeIfPressed(std::map<std::shared_ptr<Command>, Input>& pa_map,const std::shared_ptr<Command>& pa_Command) {

            auto CommandIterator = pa_map.find(pa_Command);

            if (CommandIterator != pa_map.end()) { //check if Command exists

                //type KEYBOARD
                if (CommandIterator->second.type == Input::Type::KEYBOARD)
                {
                    if (CommandIterator != pa_map.end() && IsKeyDown(CommandIterator->second.key)) {
                        CommandIterator->first->execute();
                    }
                }

                    //type BUTTON
                else if (CommandIterator->second.type == Input::Type::BUTTON && IsGamepadButtonDown(0, CommandIterator->second.button))
                {
                    CommandIterator->first->execute();
                }

                    //type AXIS
                else if (CommandIterator->second.type == Input::Type::AXIS)
                {

                    //check if the needed axis is the same as the actual input
                    if (CommandIterator->second.direction == Input::AxisDirection::Positive && GetGamepadAxisMovement(0, CommandIterator->second.axis) > CommandIterator->second.axisThreshold) {
                        CommandIterator->first->execute();
                    }
                    else if (CommandIterator->second.direction == Input::AxisDirection::Negative && GetGamepadAxisMovement(0, CommandIterator->second.axis) < CommandIterator->second.axisThreshold*-1) {
                        CommandIterator->first->execute();
                    }
                }
            }
        }


        void ButtonMapping::keyboardDefaultMapping() {

            keyboardInGameMapping.clear();

            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command>, Input> (moveUpCommand_, KEY_W ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command>, Input> (moveLeftCommand_, KEY_A ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command>, Input> (moveRightCommand_, KEY_D ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command>, Input> (moveDownCommand_, KEY_S ));

            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command>, Input> (interactCommand_, KEY_K ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command>, Input> (actionCommand_, KEY_J ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command>, Input> (disconnectCommand_, KEY_I ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command>, Input> (deathAbilityCommand_, KEY_L ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command>, Input> (highlightInteractablesCommand_, KEY_H ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command>, Input> (pauseCommand_, KEY_ESCAPE ));


            keyboardMenuMapping.clear();

            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command>, Input> (cursorUpCommand_, KEY_W ));
            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command>, Input> (cursorLeftCommand_, KEY_A ));
            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command>, Input> (cursorDownCommand_, KEY_S ));
            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command>, Input> (cursorRightCommand_, KEY_D ));

            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command>, Input> (selectCommand_, KEY_ENTER ));
            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command>, Input> (backCommand_, KEY_ESCAPE ));
        }

        void ButtonMapping::controllerDefaultMapping() {

            controllerInGameMapping.clear();

            controllerInGameMapping.insert({moveUpCommand_, Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Negative)});
            controllerInGameMapping.insert({moveLeftCommand_, Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Negative)});
            controllerInGameMapping.insert({moveDownCommand_, Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Positive)});
            controllerInGameMapping.insert({moveRightCommand_, Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Positive)});

            controllerInGameMapping.insert({interactCommand_, Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)});
            controllerInGameMapping.insert({actionCommand_, Input(GAMEPAD_BUTTON_RIGHT_TRIGGER_1)});
            controllerInGameMapping.insert({disconnectCommand_, Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)});
            controllerInGameMapping.insert({deathAbilityCommand_, Input(GAMEPAD_BUTTON_RIGHT_TRIGGER_2)});
            controllerInGameMapping.insert({highlightInteractablesCommand_, Input(GAMEPAD_BUTTON_LEFT_TRIGGER_1)});
            controllerInGameMapping.insert({pauseCommand_, Input(GAMEPAD_BUTTON_MIDDLE_RIGHT)});

            controllerMenuMapping.clear();

            controllerMenuMapping.insert({cursorUpCommand_, Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Negative)});
            controllerMenuMapping.insert({cursorLeftCommand_, Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Negative)});
            controllerMenuMapping.insert({cursorDownCommand_, Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Positive)});
            controllerMenuMapping.insert({cursorRightCommand_, Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Positive)});

            controllerMenuMapping.insert({selectCommand_, Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)});
            controllerMenuMapping.insert({backCommand_, Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)});
        }

        ButtonMapping::ButtonMapping() {

            moveUpCommand_ = std::make_shared<InGameCommand::MoveUpCommand>();
            moveLeftCommand_ = std::make_shared<InGameCommand::MoveLeftCommand>();
            moveDownCommand_ = std::make_shared<InGameCommand::MoveDownCommand>();
            moveRightCommand_ = std::make_shared<InGameCommand::MoveRightCommand>();

            interactCommand_ = std::make_shared<InGameCommand::InteractCommand>();
            actionCommand_ = std::make_shared<InGameCommand::ActionCommand>();
            disconnectCommand_ = std::make_shared<InGameCommand::DisconnectCommand>();
            deathAbilityCommand_ = std::make_shared<InGameCommand::DeathAbilityCommand>();
            highlightInteractablesCommand_ = std::make_shared<InGameCommand::HighlightInteractablesCommand>();
            pauseCommand_ = std::make_shared<InGameCommand::PauseCommand>();

            keyboardDefaultMapping();
            controllerDefaultMapping();

        }

        void ButtonMapping::testRemap() {
            std::cout << "remapping moveUp to up" << std::endl;
            remap(keyboardInGameMapping, moveUpCommand_, KEY_UP);

            std::cout << "remapping moveleft to up (to test the double assignment (move up should be A))" << std::endl;
            remap(keyboardInGameMapping, moveLeftCommand_, KEY_UP);

            std::cout << "remapping moveDown to down" << std::endl;
            remap(keyboardInGameMapping, moveDownCommand_, KEY_DOWN);

            std::cout << "remapping moveRight to right" << std::endl;
            remap(keyboardInGameMapping, moveRightCommand_, KEY_RIGHT);


            std::cout << "remapping controller moveUp to dpad up" << std::endl;
            remap(controllerInGameMapping, moveUpCommand_, Input(GAMEPAD_BUTTON_LEFT_FACE_UP));

            std::cout << "remapping controller moveleft to dpad up (to test the double assignment (move up should be left stick to left))" << std::endl;
            remap(controllerInGameMapping, moveLeftCommand_, Input(GAMEPAD_BUTTON_LEFT_FACE_UP));

            std::cout << "remapping controller moveDown to dpad down" << std::endl;
            remap(controllerInGameMapping, moveDownCommand_, Input(GAMEPAD_BUTTON_LEFT_FACE_DOWN));

            std::cout << "remapping controller moveRight to dpad right" << std::endl;
            remap(controllerInGameMapping, moveRightCommand_, Input(GAMEPAD_BUTTON_LEFT_FACE_RIGHT));
        }

        KeyboardKey ButtonMapping::detectKeyboardInput() {
//    for (int key = KEY_NULL; key < KEY_KB_MENU; key++) {
//        if (IsKeyPressed(key)) {
//            return (KeyboardKey) key;
//        }
//    }
//    return KEY_NULL;
//std::cout << "keyboard input" << std::endl;
            if (IsKeyDown(KEY_L))
            {
                std::cout << "Hilfe" << std::endl;
                return KEY_NULL;
            }
            if (IsKeyReleased(KEY_UP)){
                std::cout << "up" << std::endl;
                return KEY_UP;
            }
            else {
                std::cout << "null" << std::endl;
                return KEY_NULL;
            }
        }


    } // EventManagement
} // CoreLogic