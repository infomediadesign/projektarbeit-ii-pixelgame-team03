
#include "InputHandler.h"


void InputHandler::remap(std::map<std::shared_ptr<Command::Command>, Input>& pa_map, const std::shared_ptr<Command::Command>& pa_command, Input pa_newKey) {


    //find command & check if key is already in use
    auto commandIterator = pa_map.find(pa_command);
    for(std::pair<const std::shared_ptr<Command::Command>, Input> commandPair : pa_map) {
        if (commandPair.second == pa_newKey) {
            std::cout << "Key already in use. Swapping Keys." << std::endl;

            //save the old command and the keybind to swap (currend keybind of the command that is supposed to be rebound)
            auto usedCommand = commandPair.first;
            auto usedCommandIterator = pa_map.find(usedCommand);
            auto swappedKey = commandIterator->second;

            //erase and insert old command with swapped key
            pa_map.erase(usedCommandIterator);
            pa_map.insert(std::pair<std::shared_ptr<Command::Command>, Input>(usedCommand, swappedKey));
            break;
        }
    }

    //insert new command
    pa_map.erase(commandIterator);
    pa_map.insert(std::pair<std::shared_ptr<Command::Command>, Input>(pa_command, pa_newKey));
}


void InputHandler::checkKeyboardMovement() {
    executeIfPressed(keyboardInGameMapping, moveUpCommand_);
    executeIfPressed(keyboardInGameMapping, moveDownCommand_);
    executeIfPressed(keyboardInGameMapping, moveLeftCommand_);
    executeIfPressed(keyboardInGameMapping, moveRightCommand_);
}

void InputHandler::checkControllerMovement() {
    executeIfPressed(controllerInGameMapping, moveUpCommand_);
    executeIfPressed(controllerInGameMapping, moveDownCommand_);
    executeIfPressed(controllerInGameMapping, moveLeftCommand_);
    executeIfPressed(controllerInGameMapping, moveRightCommand_);
}

void InputHandler::executeIfPressed(std::map<std::shared_ptr<Command::Command>, Input>& pa_map,const std::shared_ptr<Command::Command>& pa_command) {

    auto commandIterator = pa_map.find(pa_command);

    if (commandIterator != pa_map.end()) { //check if command exists

        //type KEYBOARD
        if (commandIterator->second.type == Input::Type::KEYBOARD)
        {
            if (commandIterator != pa_map.end() && IsKeyDown(commandIterator->second.key)) {
                commandIterator->first->execute();
            }
        }

        //type BUTTON
        else if (commandIterator->second.type == Input::Type::BUTTON && IsGamepadButtonDown(0, commandIterator->second.button))
        {
            commandIterator->first->execute();
        }

        //type AXIS
        else if (commandIterator->second.type == Input::Type::AXIS)
        {

            //check if the needed axis is the same as the actual input
            if (commandIterator->second.direction == Input::AxisDirection::Positive && GetGamepadAxisMovement(0, commandIterator->second.axis) > commandIterator->second.axisThreshold) {
                commandIterator->first->execute();
            }
            else if (commandIterator->second.direction == Input::AxisDirection::Negative && GetGamepadAxisMovement(0, commandIterator->second.axis) < commandIterator->second.axisThreshold*-1) {
                commandIterator->first->execute();
            }
        }
    }
}


void InputHandler::keyboardDefaultMapping() {

    keyboardInGameMapping.clear();

    keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (moveUpCommand_, KEY_W ));
    keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (moveLeftCommand_, KEY_A ));
    keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (moveRightCommand_, KEY_D ));
    keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (moveDownCommand_, KEY_S ));

    keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (interactCommand_, KEY_K ));
    keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (actionCommand_, KEY_J ));
    keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (disconnectCommand_, KEY_I ));
    keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (deathAbilityCommand_, KEY_L ));
    keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (highlightInteractablesCommand_, KEY_H ));
    keyboardInGameMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (pauseCommand_, KEY_ESCAPE ));


    keyboardMenuMapping.clear();

    keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (std::make_unique<Command::CursorUpCommand>(), KEY_W ));
    keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (std::make_unique<Command::CursorLeftCommand>(), KEY_A ));
    keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (std::make_unique<Command::CursorDownCommand>(), KEY_S ));
    keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (std::make_unique<Command::CursorRightCommand>(), KEY_D ));

    keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (std::make_unique<Command::SelectCommand>(), KEY_ENTER ));
    keyboardMenuMapping.insert (std::pair<std::shared_ptr<Command::Command>, Input> (std::make_unique<Command::BackCommand>(), KEY_ESCAPE ));
}

void InputHandler::controllerDefaultMapping() {

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

    controllerMenuMapping.insert({std::make_shared<Command::CursorUpCommand>(), Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Negative)});
    controllerMenuMapping.insert({std::make_shared<Command::CursorLeftCommand>(), Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Negative)});
    controllerMenuMapping.insert({std::make_shared<Command::CursorDownCommand>(), Input(GAMEPAD_AXIS_LEFT_Y, Input::AxisDirection::Positive)});
    controllerMenuMapping.insert({std::make_shared<Command::CursorRightCommand>(), Input(GAMEPAD_AXIS_LEFT_X, Input::AxisDirection::Positive)});

    controllerMenuMapping.insert({std::make_shared<Command::SelectCommand>(), Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)});
    controllerMenuMapping.insert({std::make_shared<Command::BackCommand>(), Input(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)});
}

InputHandler::InputHandler() {
    
    moveUpCommand_ = std::make_shared<Command::MoveUpCommand>();
    moveLeftCommand_ = std::make_shared<Command::MoveLeftCommand>();
    moveDownCommand_ = std::make_shared<Command::MoveDownCommand>();
    moveRightCommand_ = std::make_shared<Command::MoveRightCommand>();
    
    interactCommand_ = std::make_shared<Command::InteractCommand>();
    actionCommand_ = std::make_shared<Command::ActionCommand>();
    disconnectCommand_ = std::make_shared<Command::DisconnectCommand>();
    deathAbilityCommand_ = std::make_shared<Command::DeathAbilityCommand>();
    highlightInteractablesCommand_ = std::make_shared<Command::HighlightInteractablesCommand>();
    pauseCommand_ = std::make_shared<Command::PauseCommand>();
    
    keyboardDefaultMapping();
    controllerDefaultMapping();

}

void InputHandler::testRemap() {
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

//KeyboardKey InputHandler::detectKeyboardInput() {
//    for (int key = KEY_NULL; key < KEY_KB_MENU; key++) {
//        if (IsKeyPressed(key)) {
//            return (KeyboardKey) key;
//        }
//    }
//    return KEY_NULL;
//}

