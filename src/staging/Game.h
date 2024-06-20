//
// Created by keanu on 5/26/2024.
//

#ifndef RAYLIBSTARTER_GAME_H
#define RAYLIBSTARTER_GAME_H


#include <string>
#include <memory>
#include "raylib.h"
#include "Stage.h"
#include <iostream>



namespace Staging
{
    class Game final
    {
    public:
        Game() = delete;

        Game(int pa_stage_width, int pa_stage_height, int pa_target_fps,
             int pa_window_flags, int pa_exit_key, bool pa_audio, bool pa_fullscreen, const std::string& pa_game_title);

        Game(const Staging::Game &game) = delete;
        Game &operator=(const Game &) = delete;

        void run();

        ~Game();

    private:
        const int stageWidth_;
        const int stageHeight_;
        const int targetFPS_;
        const int windowFlags_;
        const int exitKey_;

        std::unique_ptr<::Staging::Stage> stage_;

        const std::string gameTitle_;


        bool fullscreen_;
        bool audio_;

    };
}






#endif //RAYLIBSTARTER_GAME_H
