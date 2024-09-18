//
// Created by keanu on 9/5/2024.
//

#ifndef HIVE_DESIGNCONFIG_H
#define HIVE_DESIGNCONFIG_H

#include <raylib.h>

namespace CoreLogic::DataProcessing {
    class DesignConfig final
    {

        /**
         * @attention: never change anything before the equal sign. Those are the names of the variables and the code will break if anything there is touched.
         * anything right of the equal sign can be changes as desired unless there is a comment saying otherwise.
         *
         * 1 tick is 1/60th of a second
         */

    public:

        //drone life; in life
        inline static constexpr int STARTING_MAX_DRONE_LIFE = 3;
        inline static constexpr int STARTING_CURRENT_DRONE_LIFE = 3;
        inline static constexpr int REGENERATION_LIFE = 2;

        //volume; in 0.0f - 1.0f
        inline static constexpr float MUSIC_VOLUME = 0.4f;
        inline static constexpr float SFX_VOLUME = 0.1f;

        //drone speed; in pixel per tick
        inline static constexpr int DRONE_SPEED = 2;
        inline static constexpr int WORKER_SPEED = 2;
        inline static constexpr int SCOUT_SPEED = 3;

        //range; in tiles
        inline static constexpr int COLONIST_RANGE = 8;
        inline static constexpr int MECH_RANGE = 4;
        inline static constexpr int BELL_DETECTION_TILES = 20;

        //detection rate; in ticks
        inline static constexpr int COLONIST_DETECTION_RATE = 90;
        inline static constexpr int MECH_DETECTION_RATE = 60;

        //how long enemies are turned by the bell; in ticks
        inline static constexpr int BELL_TURN_TIME = 1200;


        //axis threshold (how much tolerance the joysticks have when detecting input (0.0f = no tolerance, 1.0f = tbd))
        inline static constexpr float AXIS_THRESHOLD = 0.5f;

        //default controller mapping; strg click on the right side to be navigated to a list of names of all available buttons.
        inline static constexpr GamepadButton INTERACT_CONTROLLER = GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
        inline static constexpr GamepadButton ABILITY_CONTROLLER = GAMEPAD_BUTTON_RIGHT_FACE_LEFT;
        inline static constexpr GamepadButton DISCONNECT_CONTROLLER = GAMEPAD_BUTTON_RIGHT_FACE_UP;
        inline static constexpr GamepadButton DEATH_ABILITY_CONTROLLER = GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;

        inline static constexpr GamepadButton MENU_CONFIRM_CONTROLLER = GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
        inline static constexpr GamepadButton MENU_BACK_CONTROLLER = GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;

        inline static constexpr GamepadButton PAUSE_CONTROLLER = GAMEPAD_BUTTON_MIDDLE_RIGHT;
        inline static constexpr GamepadButton EXIT_CONTROLLER = GAMEPAD_BUTTON_MIDDLE_LEFT;

        //default keyboard mapping; strg click on the right side to be navigated to a list of names of all available keys.
        inline static constexpr KeyboardKey INTERACT_KEYBOARD = KEY_K;
        inline static constexpr KeyboardKey ABILITY_KEYBOARD = KEY_J;
        inline static constexpr KeyboardKey DISCONNECT_KEYBOARD = KEY_I;
        inline static constexpr KeyboardKey DEATH_ABILITY_KEYBOARD = KEY_L;

        inline static constexpr KeyboardKey MENU_CONFIRM_KEYBOARD = KEY_ENTER;
        inline static constexpr KeyboardKey MENU_BACK_KEYBOARD = KEY_BACKSPACE;

        inline static constexpr KeyboardKey PAUSE_KEYBOARD = KEY_ESCAPE;
        inline static constexpr KeyboardKey EXIT_KEY = KEY_DELETE;
    };

    //#define GAME_START_FULLSCREEN
}
#endif //HIVE_DESIGNCONFIG_H
