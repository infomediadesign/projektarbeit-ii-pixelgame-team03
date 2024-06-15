//
// Created by Josi on 07.06.2024.
//

#ifndef HIVE_BUTTONMAPPING_H
#define HIVE_BUTTONMAPPING_H

#include <raylib.h>
#include <memory>
#include <map>
#include "Commands.h"

namespace CoreLogic::EventManagement {

        class ButtonMapping {
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
                bool activated = false;

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
            ButtonMapping();

            void keyboardDefaultMapping();

            void controllerDefaultMapping();

            void testRemap();

            void checkKeyboardMovement();

            void checkControllerMovement();

            void remap(std::map<std::shared_ptr<Command>, Input> &pa_map,
                       const std::shared_ptr<Command> &pa_Command, Input pa_newInput);

            bool isAxisPressed(Input& pa_axis);
            bool isAxisReleased(Input& pa_axis);

            //Input detection
            KeyboardKey detectKeyboardInput();

        protected:
            std::map<std::shared_ptr<Command>, Input> keyboardInGameMapping;
            std::map<std::shared_ptr<Command>, Input> keyboardMenuMapping;

            std::map<std::shared_ptr<Command>, Input> controllerInGameMapping;
            std::map<std::shared_ptr<Command>, Input> controllerMenuMapping;


            std::shared_ptr<InGameCommand::MoveUpCommand> moveUpCommand_;
            std::shared_ptr<InGameCommand::MoveLeftCommand> moveLeftCommand_;
            std::shared_ptr<InGameCommand::MoveDownCommand> moveDownCommand_;
            std::shared_ptr<InGameCommand::MoveRightCommand> moveRightCommand_;

            std::shared_ptr<InGameCommand::InteractCommand> interactCommand_;
            std::shared_ptr<InGameCommand::ActionCommand> actionCommand_;
            std::shared_ptr<InGameCommand::DisconnectCommand> disconnectCommand_;
            std::shared_ptr<InGameCommand::DeathAbilityCommand> deathAbilityCommand_;
            std::shared_ptr<InGameCommand::HighlightInteractablesCommand> highlightInteractablesCommand_;
            std::shared_ptr<InGameCommand::PauseCommand> pauseCommand_;


            std::shared_ptr<MenuCommand::CursorUpCommand> cursorUpCommand_;
            std::shared_ptr<MenuCommand::CursorLeftCommand> cursorLeftCommand_;
            std::shared_ptr<MenuCommand::CursorDownCommand> cursorDownCommand_;
            std::shared_ptr<MenuCommand::CursorRightCommand> cursorRightCommand_;

            std::shared_ptr<MenuCommand::SelectCommand> selectCommand_;
            std::shared_ptr<MenuCommand::BackCommand> backCommand_;
        };

}

#endif //HIVE_BUTTONMAPPING_H
