//
// Created by Josi on 19.09.2024.
//

#include "CreditScene.h"
#include "event_management/SoundHandler.h"

Scenes::CreditScene::CreditScene()
{
    background_ = CoreLogic::DataProcessing::SpriteStorage::getSprite
            (CoreLogic::DataProcessing::SpriteStorage::CREDIT_SCENE);
}

void Scenes::CreditScene::draw(RenderTexture2D &pa_canvas)
{
    CoreLogic::EventManagement::SoundHandler &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
    soundHandler.update();

    ClearBackground(BLACK);
    BeginTextureMode(pa_canvas);
    {
        DrawTexturePro(background_.getTexture(), background_.getFrame(), {0, 0, 640, 360}, {0, 0}, 0, WHITE);
//        DrawTextPro(CoreLogic::DataProcessing::Fonts::getFont(0), "Press ENTER to continue",
//                {640 - 200, 360 - 30}, {0, 0}, 0,
//                20, 0, WHITE);
    }
    EndTextureMode();
}

void Scenes::CreditScene::update()
{
    auto &inputHandler = CoreLogic::EventManagement::InputHandler::getInstance();
    std::vector<CoreLogic::EventManagement::EventEnum> events = inputHandler.handleInput();

    for (CoreLogic::EventManagement::EventEnum event: events)
    {
        if (event == CoreLogic::EventManagement::ENTER)
        {
            CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::IN_GAME);
        }
    }

    background_.shiftFrame(!CoreLogic::EventManagement::InputHandler::gatLastInputKeyboard());
}

void Scenes::CreditScene::onSwitch()
{
    update();
}
