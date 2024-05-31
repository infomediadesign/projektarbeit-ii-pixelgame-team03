

#ifndef GITKEEP_INPUTHANDLER_H
#define GITKEEP_INPUTHANDLER_H

#include "qualityOfLife.h"
#include "Commands/allCommands.h"
#include "actor.h"


class InputHandler {

    struct Input {
        enum Type {
            BUTTON,
            AXIS,
            KEYBOARD
        } type;

        union {
            GamepadButton button;
            GamepadAxis axis;
            KeyboardKey key;
        };

        enum AxisDirection {
            Positive,
            Negative
        } direction;

        float axisThreshold = 0.5f;

        Input(GamepadButton btn) : type(BUTTON), button(btn) {}

        Input(GamepadAxis ax, AxisDirection dir) : type(AXIS), axis(ax), direction(dir) {}

        Input(KeyboardKey k) : type(KEYBOARD), key(k) {}

        bool operator==(const Input &other) const {
            if (type != other.type) return false;
            if (type == BUTTON) return button == other.button;
            if (type == AXIS) return axis == other.axis && direction == other.direction;
            if (type == KEYBOARD) return key == other.key;
        }
    };

public:
    InputHandler();

    void keyboardDefaultMapping();

    void controllerDefaultMapping();

    void testRemap();

    void checkKeyboardMovement();

    void checkControllerMovement();

    void remap(std::map<std::shared_ptr<Command::Command>, Input> &pa_map,
               const std::shared_ptr<Command::Command> &pa_command, Input pa_newInput);

    void executeIfPressed(std::map<std::shared_ptr<Command::Command>, Input> &pa_map,
                          const std::shared_ptr<Command::Command> &pa_command);

    //Input detection

protected:
    std::map<std::shared_ptr<Command::Command>, Input> keyboardInGameMapping;
    std::map<std::shared_ptr<Command::Command>, Input> keyboardMenuMapping;

    std::map<std::shared_ptr<Command::Command>, Input> controllerInGameMapping;
    std::map<std::shared_ptr<Command::Command>, Input> controllerMenuMapping;


    std::shared_ptr<Command::MoveUpCommand> moveUpCommand_;
    std::shared_ptr<Command::MoveLeftCommand> moveLeftCommand_;
    std::shared_ptr<Command::MoveDownCommand> moveDownCommand_;
    std::shared_ptr<Command::MoveRightCommand> moveRightCommand_;

    std::shared_ptr<Command::InteractCommand> interactCommand_;
    std::shared_ptr<Command::ActionCommand> actionCommand_;
    std::shared_ptr<Command::DisconnectCommand> disconnectCommand_;
    std::shared_ptr<Command::DeathAbilityCommand> deathAbilityCommand_;
    std::shared_ptr<Command::HighlightInteractablesCommand> highlightInteractablesCommand_;
    std::shared_ptr<Command::PauseCommand> pauseCommand_;


    std::shared_ptr<Command::CursorUpCommand> cursorUpCommand_;
    std::shared_ptr<Command::CursorLeftCommand> cursorLeftCommand_;
    std::shared_ptr<Command::CursorDownCommand> cursorDownCommand_;
    std::shared_ptr<Command::CursorRightCommand> cursorRightCommand_;

    std::shared_ptr<Command::SelectCommand> selectCommand_;
    std::shared_ptr<Command::BackCommand> backCommand_;
};


#endif //GITKEEP_INPUTHANDLER_H
