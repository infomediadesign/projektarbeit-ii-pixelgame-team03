//
// Created by keanu on 5/26/2024.
//

#include "MainMenuScene.h"
#include "event_management/SoundHandler.h"
#include "../staging/Game.h"

Scenes::MainMenuScene::MainMenuScene(): Scene(std::make_shared<Camera2D>())
{
    sprite_ = CoreLogic::DataProcessing::SpriteStorage::getSprite(CoreLogic::DataProcessing::SpriteStorage::MAIN_MENU);
}

void Scenes::MainMenuScene::draw(RenderTexture2D &pa_canvas)
{
    ClearBackground(BLACK);
    BeginTextureMode(pa_canvas);
    {
        DrawTexturePro(sprite_.getTexture(), sprite_.getFrame(), {0, 0, 640, 360}, {0, 0}, 0, WHITE);
    }
    EndTextureMode();
}

void Scenes::MainMenuScene::update()
{
    CoreLogic::EventManagement::SoundHandler &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
    soundHandler.update();

    std::vector<CoreLogic::EventManagement::EventEnum> events = po_inputHandler_->handleInput();

    for (CoreLogic::EventManagement::EventEnum event : events)
    {
        if (event == CoreLogic::EventManagement::INTERACT)
        {
            if (exitGame_)
            {
                Staging::Game::requestExit();
            } else {
                CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::IN_GAME);
            }

        } else if (event == CoreLogic::EventManagement::MOVE_DOWN) {
            if (!exitGame_) {
                exitGame_ = true;
                sprite_.shiftFrame(exitGame_);
            }
        } else if (event == CoreLogic::EventManagement::MOVE_UP) {
            if (exitGame_) {
                exitGame_ = false;
                sprite_.shiftFrame(exitGame_);
            }
        }
    }
}

void Scenes::MainMenuScene::onSwitch()
{
    update();
}
