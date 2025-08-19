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
    auto &inputHandler = CoreLogic::EventManagement::InputHandler::getInstance();
    std::vector<CoreLogic::EventManagement::EventEnum> events = inputHandler.handleInput();

    for (CoreLogic::EventManagement::EventEnum event : events)
    {
        if (event == CoreLogic::EventManagement::ENTER)
        {
            if (startGame_)
            {
                CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::IN_GAME);
            } else {
                Staging::Game::requestExit();
            }

        } else if (event == CoreLogic::EventManagement::MOVE_DOWN) {
            if (startGame_) {
                startGame_ = false;
                sprite_.shiftFrame(1);
            }
        } else if (event == CoreLogic::EventManagement::MOVE_UP) {
            if (!startGame_) {
                startGame_ = true;
                sprite_.shiftFrame(0);
            }
        }
    }
}

void Scenes::MainMenuScene::onSwitch()
{
    update();
}
