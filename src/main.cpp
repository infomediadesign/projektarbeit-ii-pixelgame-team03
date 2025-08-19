#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>

#include "raylib.h"
#include "tileson.h"

#include "config.h"
#include "staging/Game.h"
#include "Game.h"


int main() {

    Staging::Game game(GameSpace::Config::Def_ScreenWidth, GameSpace::Config::Def_ScreenHeight,
                                  GameSpace::Config::Def_TargetFPS, GameSpace::Config::Def_WindowFlags,
                                  GameSpace::Config::Def_ExitKey,
                                  GameSpace::Config::Def_Audio, GameSpace::Config::Def_FullScreen,
                                  GameSpace::Config::PROJECT_NAME);

    game.run();

    CloseWindow();
    return EXIT_SUCCESS;
}

/**
 * @brief: As this is the date of official Copletion of the Project, we will leave here for you a wonderful List(TM) of
 *         repairs to our code that would have made the whole codebase much much prettier.
 *         We are wholly aware that many things could have been cleaner as they were at certain points added primarily
 *         hard-coded, as to try it out first and then make it pretty second.
 *         Obviously we never truly got to this point.
 *         We still feel as though our Code is very well structured and serves our purposes very well. Most things to
 *         clean up would not actually add much functionality and would rather just improve upon the accessibility for
 *         our Designers or just look nicer because a few main functions would be less overused.
 *
 *         Anyway at the end of all this we leave you with the final To-do List:
 *         1.@todo: clean up the GameScene.update() func so it has access to private funcs that outsouce its work
 *         2.@todo: generally rework all hardcoded values (like the camera bounds, tile size in some areas etc.)
 *         3.@todo: make the Game framerate independent using deltaTime
 *         4.@todo: custom button mapping
 *         5.@todo: Menus to access button mapping, sound settings and similar
 *         6.@todo: Multithread Drawing, Sound, Update
 *         7.@todo: Animated environment(is easy, but not all animations exist yet, so code hasn't been added yet either)
 *
 *
 *         With this we will bid you adieu.
 *         - @author: Keanu Grespan, Josefine Chollé @date: 2024/9/19
 *
 **/