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
