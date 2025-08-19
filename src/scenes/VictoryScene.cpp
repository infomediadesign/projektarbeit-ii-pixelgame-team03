//
// Created by Josi on 13.09.2024.
//

#include "VictoryScene.h"

namespace Scenes
{

    VictoryScene::VictoryScene(): Scene(std::make_shared<Camera2D>())
    {
        background_ = CoreLogic::DataProcessing::SpriteStorage::getSprite(CoreLogic::DataProcessing::SpriteStorage::VICTORY_BACKGROUND);
        buttons_ = CoreLogic::DataProcessing::SpriteStorage::getSprite(CoreLogic::DataProcessing::SpriteStorage::VICTORY_BUTTONS);
    }

    void VictoryScene::draw(RenderTexture2D &pa_canvas)
    {
        // do the blinky blink
        ClearBackground(BLACK);
        BeginTextureMode(pa_canvas);
        {
            DrawTexturePro(background_.getTexture(), background_.getFrame(), {0, 0, 640, 360}, {0, 0}, 0, WHITE);
            if (handleInput_)
            {
                DrawTexturePro(buttons_.getTexture(), buttons_.getFrame(), {0, 0, 640, 360}, {0, 0}, 0, WHITE);
            }
        }
        EndTextureMode();
    }

    void VictoryScene::update()
    {
        if (handleInput_)
        {
            updateInput();
            return;
        }
        //shift frame your way through this

        if (loopdyloops_ < 11)
        {
            if (CoreLogic::DataProcessing::global_ticks % 10 == 0)
            {
                background_.shiftFrame(0);
                loopdyloops_++;
            }
        } else {
            handleInput_ = true;
        }

    }

    void VictoryScene::updateInput()
    {
        auto &inputHandler = CoreLogic::EventManagement::InputHandler::getInstance();
        std::vector<CoreLogic::EventManagement::EventEnum> events = inputHandler.handleInput();

        for (CoreLogic::EventManagement::EventEnum event : events)
        {
            if (event == CoreLogic::EventManagement::ENTER)
            {
                if (!restartGame_)
                {
                    CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::MAIN_MENU);
                } else {
                    CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::IN_GAME);
                }

            } else if (event == CoreLogic::EventManagement::MOVE_DOWN) {
                if (restartGame_) {
                    restartGame_ = false;
                    buttons_.shiftFrame(1);
                }
            } else if (event == CoreLogic::EventManagement::MOVE_UP) {
                if (!restartGame_) {
                    restartGame_ = true;
                    buttons_.shiftFrame(0);
                }
            }
        }
    }

    void VictoryScene::onSwitch()
    {
        loopdyloops_ = 0;
        update();
    }
} // Scenes