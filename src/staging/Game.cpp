//
// Created by keanu on 5/26/2024.
//


#include "Game.h"

bool Staging::Game::running_;

Staging::Game::Game(int pa_stage_width, int pa_stage_height, int pa_target_fps, int pa_window_flags,
                    int pa_exit_key, bool pa_audio, bool pa_fullscreen,
                    const std::string &pa_game_title) : stageWidth_(pa_stage_width), gameTitle_(pa_game_title),
                                                          stageHeight_(pa_stage_height), targetFPS_(pa_target_fps),
                                                          windowFlags_(pa_window_flags), exitKey_(pa_exit_key),
                                                          fullscreen_(pa_fullscreen), audio_(pa_audio)


{
    SetConfigFlags(windowFlags_);
    InitWindow(stageWidth_, stageHeight_, gameTitle_.c_str());
    SetExitKey(CoreLogic::DataProcessing::DesignConfig::EXIT_KEY);
    SetWindowMinSize(stageWidth_, stageHeight_);
    SetTargetFPS(targetFPS_);
    CoreLogic::DataProcessing::TileMap::Initialize();
    CoreLogic::DataProcessing::ActorStorage::Initialize();
    CoreLogic::DataProcessing::SpriteStorage::Initialize();
    CoreLogic::DataProcessing::StateMachine::Initialize();
    CoreLogic::DataProcessing::Fonts::Initialize();

    fullscreen_ = pa_fullscreen;
    audio_ = pa_audio;
    if (fullscreen_)
    {
        ToggleFullscreen();
    }
    if (audio_)
    {
        InitAudioDevice();
    }

    po_stage_ = std::make_unique<Staging::Stage>(stageHeight_, stageWidth_);
    TraceLog(LOG_INFO, "GameSpace Initialized");
}

Staging::Game::~Game()
{
    TraceLog(LOG_INFO, "GameSpace Terminated");
    if (audio_)
    {
        CloseAudioDevice();
    }
//    CloseWindow();
}

void Staging::Game::run()
{
    running_ = true;
    while (running_)
    {
        if (WindowShouldClose())
        {
            running_ = false;
        }

        if (IsKeyPressed(KEY_F11))
        {
            if (IsWindowFullscreen())
            {
                ToggleFullscreen();
                SetWindowSize(stageWidth_, stageHeight_);
            } else {
                SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
                ToggleFullscreen();
            }
        }
        po_stage_->update();

        po_stage_->draw();
    }
}

void Staging::Game::requestExit()
{
    running_ = false;
}


