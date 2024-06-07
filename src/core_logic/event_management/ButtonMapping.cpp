//
// Created by Josi on 07.06.2024.
//

#include "ButtonMapping.h"
#include <iostream>

namespace CoreLogic {
    namespace EventManagement {


        void ButtonMapping::remap(std::map<std::shared_ptr<Comand>, Input>& pa_map, const std::shared_ptr<Comand>& pa_Comand, Input pa_newKey) {

            KeyboardKey newKey;
            while (detectKeyboardInput() != KEY_NULL) {
                std::cout << "clearing previous key" << std::endl;

            }
            std::cout << "cleared previous key" << std::endl;
            while (IsKeyDown(KEY_NULL)) {
                std::cout << "new key" << std::endl;
            }

            //find Comand & check if key is already in use
            auto ComandIterator = pa_map.find(pa_Comand);
            for(std::pair<const std::shared_ptr<Comand>, Input> ComandPair : pa_map) {
                if (ComandPair.second == newKey) {
                    std::cout << "Key already in use. Swapping Keys." << std::endl;

                    //save the old Comand and the keybind to swap (currend keybind of the Comand that is supposed to be rebound)
                    auto usedComand = ComandPair.first;
                    auto usedComandIterator = pa_map.find(usedComand);
                    auto swappedKey = ComandIterator->second;

                    //erase and insert old Comand with swapped key
                    pa_map.erase(usedComandIterator);
                    pa_map.insert(std::pair<std::shared_ptr<Comand>, Input>(usedComand, swappedKey));
                    break;
                }
            }

            //insert new Comand
            pa_map.erase(ComandIterator);
            pa_map.insert(std::pair<std::shared_ptr<Comand>, Input>(pa_Comand, newKey));
        }


        void ButtonMapping::checkKeyboardMovement() {
            executeIfPressed(keyboardInGameMapping, moveUpComand_);
            executeIfPressed(keyboardInGameMapping, moveDownComand_);
            executeIfPressed(keyboardInGameMapping, moveLeftComand_);
            executeIfPressed(keyboardInGameMapping, moveRightComand_);
        }

        void ButtonMapping::checkControllerMovement() {
            executeIfPressed(controllerInGameMapping, moveUpComand_);
            executeIfPressed(controllerInGameMapping, moveDownComand_);
            executeIfPressed(controllerInGameMapping, moveLeftComand_);
            executeIfPressed(controllerInGameMapping, moveRightComand_);
        }

        void ButtonMapping::executeIfPressed(std::map<std::shared_ptr<Comand>, Input>& pa_map,const std::shared_ptr<Comand>& pa_Comand) {

            auto ComandIterator = pa_map.find(pa_Comand);

            if (ComandIterator != pa_map.end()) { //check if Comand exists

                //type KEYBOARD
                if (ComandIterator->second.type == Input::Type::KEYBOARD)
                {
                    if (ComandIterator != pa_map.end() && IsKeyDown(ComandIterator->second.key)) {
                        ComandIterator->first->execute();
                    }
                }

                    //type BUTTON
                else if (ComandIterator->second.type == Input::Type::BUTTON && IsGamepadButtonDown(0, ComandIterator->second.button))
                {
                    ComandIterator->first->execute();
                }

                    //type AXIS
                else if (ComandIterator->second.type == Input::Type::AXIS)
                {

                    //check if the needed axis is the same as the actual input
                    if (ComandIterator->second.direction == Input::AxisDirection::Positive && GetGamepadAxisMovement(0, ComandIterator->second.axis) > ComandIterator->second.axisThreshold) {
                        ComandIterator->first->execute();
                    }
                    else if (ComandIterator->second.direction == Input::AxisDirection::Negative && GetGamepadAxisMovement(0, ComandIterator->second.axis) < ComandIterator->second.axisThreshold*-1) {
                        ComandIterator->first->execute();
                    }
                }
            }
        }


        void ButtonMapping::keyboardDefaultMapping() {

            keyboardInGameMapping.clear();

            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (moveUpComand_, KEY_W ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (moveLeftComand_, KEY_A ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (moveRightComand_, KEY_D ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (moveDownComand_, KEY_S ));

            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (interactComand_, KEY_K ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (actionComand_, KEY_J ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (disconnectComand_, KEY_I ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (deathAbilityComand_, KEY_L ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (highlightInteractablesComand_, KEY_H ));
            keyboardInGameMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (pauseComand_, KEY_ESCAPE ));


            keyboardMenuMapping.clear();

            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (cursorUpComand_, KEY_W ));
            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (cursorLeftComand_, KEY_A ));
            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (cursorDownComand_, KEY_S ));
            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (cursorRightComand_, KEY_D ));

            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (selectComand_, KEY_ENTER ));
            keyboardMenuMapping.insert (std::pair<std::shared_ptr<Comand>, Input> (backComand_, KEY_ESCAPE ));
        }

        void ButtonMapping::controllerDefaultMapping() {

            controllerInGameMapping.clear();

            controllerInGameMapping.insert({moveUpComand_, Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Negative)});
            controllerInGameMapping.insert({moveLeftComand_, Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Negative)});
            controllerInGameMapping.insert({moveDownComand_, Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Positive)});
            controllerInGameMapping.insert({moveRightComand_, Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Positive)});

            controllerInGameMapping.insert({interactComand_, Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)});
            controllerInGameMapping.insert({actionComand_, Input(GAMEPAD_BUTTON_RIGHT_TRIGGER_1)});
            controllerInGameMapping.insert({disconnectComand_, Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)});
            controllerInGameMapping.insert({deathAbilityComand_, Input(GAMEPAD_BUTTON_RIGHT_TRIGGER_2)});
            controllerInGameMapping.insert({highlightInteractablesComand_, Input(GAMEPAD_BUTTON_LEFT_TRIGGER_1)});
            controllerInGameMapping.insert({pauseComand_, Input(GAMEPAD_BUTTON_MIDDLE_RIGHT)});

            controllerMenuMapping.clear();

            controllerMenuMapping.insert({cursorUpComand_, Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Negative)});
            controllerMenuMapping.insert({cursorLeftComand_, Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Negative)});
            controllerMenuMapping.insert({cursorDownComand_, Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Positive)});
            controllerMenuMapping.insert({cursorRightComand_, Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Positive)});

            controllerMenuMapping.insert({selectComand_, Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)});
            controllerMenuMapping.insert({backComand_, Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)});
        }

        ButtonMapping::ButtonMapping() {

            moveUpComand_ = std::make_shared<InGameComand::MoveUpComand>();
            moveLeftComand_ = std::make_shared<InGameComand::MoveLeftComand>();
            moveDownComand_ = std::make_shared<InGameComand::MoveDownComand>();
            moveRightComand_ = std::make_shared<InGameComand::MoveRightComand>();

            interactComand_ = std::make_shared<InGameComand::InteractComand>();
            actionComand_ = std::make_shared<InGameComand::ActionComand>();
            disconnectComand_ = std::make_shared<InGameComand::DisconnectComand>();
            deathAbilityComand_ = std::make_shared<InGameComand::DeathAbilityComand>();
            highlightInteractablesComand_ = std::make_shared<InGameComand::HighlightInteractablesComand>();
            pauseComand_ = std::make_shared<InGameComand::PauseComand>();

            keyboardDefaultMapping();
            controllerDefaultMapping();

        }

        void ButtonMapping::testRemap() {
            std::cout << "remapping moveUp to up" << std::endl;
            remap(keyboardInGameMapping, moveUpComand_, KEY_UP);

            std::cout << "remapping moveleft to up (to test the double assignment (move up should be A))" << std::endl;
            remap(keyboardInGameMapping, moveLeftComand_, KEY_UP);

            std::cout << "remapping moveDown to down" << std::endl;
            remap(keyboardInGameMapping, moveDownComand_, KEY_DOWN);

            std::cout << "remapping moveRight to right" << std::endl;
            remap(keyboardInGameMapping, moveRightComand_, KEY_RIGHT);


            std::cout << "remapping controller moveUp to dpad up" << std::endl;
            remap(controllerInGameMapping, moveUpComand_, Input(GAMEPAD_BUTTON_LEFT_FACE_UP));

            std::cout << "remapping controller moveleft to dpad up (to test the double assignment (move up should be left stick to left))" << std::endl;
            remap(controllerInGameMapping, moveLeftComand_, Input(GAMEPAD_BUTTON_LEFT_FACE_UP));

            std::cout << "remapping controller moveDown to dpad down" << std::endl;
            remap(controllerInGameMapping, moveDownComand_, Input(GAMEPAD_BUTTON_LEFT_FACE_DOWN));

            std::cout << "remapping controller moveRight to dpad right" << std::endl;
            remap(controllerInGameMapping, moveRightComand_, Input(GAMEPAD_BUTTON_LEFT_FACE_RIGHT));
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