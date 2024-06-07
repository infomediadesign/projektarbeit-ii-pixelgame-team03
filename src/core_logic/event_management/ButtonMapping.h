//
// Created by Josi on 07.06.2024.
//

#ifndef HIVE_BUTTONMAPPING_H
#define HIVE_BUTTONMAPPING_H

#include <raylib.h>
#include <memory>
#include <map>
#include "Comands.h"

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

            void remap(std::map<std::shared_ptr<Comand>, Input> &pa_map,
                       const std::shared_ptr<Comand> &pa_Comand, Input pa_newInput);

            void executeIfPressed(std::map<std::shared_ptr<Comand>, Input> &pa_map,
                                  const std::shared_ptr<Comand> &pa_Comand);

            //Input detection
            KeyboardKey detectKeyboardInput();

        protected:
            std::map<std::shared_ptr<Comand>, Input> keyboardInGameMapping;
            std::map<std::shared_ptr<Comand>, Input> keyboardMenuMapping;

            std::map<std::shared_ptr<Comand>, Input> controllerInGameMapping;
            std::map<std::shared_ptr<Comand>, Input> controllerMenuMapping;


            std::shared_ptr<InGameComand::MoveUpComand> moveUpComand_;
            std::shared_ptr<InGameComand::MoveLeftComand> moveLeftComand_;
            std::shared_ptr<InGameComand::MoveDownComand> moveDownComand_;
            std::shared_ptr<InGameComand::MoveRightComand> moveRightComand_;

            std::shared_ptr<InGameComand::InteractComand> interactComand_;
            std::shared_ptr<InGameComand::ActionComand> actionComand_;
            std::shared_ptr<InGameComand::DisconnectComand> disconnectComand_;
            std::shared_ptr<InGameComand::DeathAbilityComand> deathAbilityComand_;
            std::shared_ptr<InGameComand::HighlightInteractablesComand> highlightInteractablesComand_;
            std::shared_ptr<InGameComand::PauseComand> pauseComand_;


            std::shared_ptr<MenuComand::CursorUpComand> cursorUpComand_;
            std::shared_ptr<MenuComand::CursorLeftComand> cursorLeftComand_;
            std::shared_ptr<MenuComand::CursorDownComand> cursorDownComand_;
            std::shared_ptr<MenuComand::CursorRightComand> cursorRightComand_;

            std::shared_ptr<MenuComand::SelectComand> selectComand_;
            std::shared_ptr<MenuComand::BackComand> backComand_;
        };

}

#endif //HIVE_BUTTONMAPPING_H
