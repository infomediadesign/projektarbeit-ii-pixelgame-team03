//
// Created by Josi on 13.09.2024.
//

#include "NoteScene.h"
#include "event_management/SoundHandler.h"


Scenes::NoteScene::NoteScene(): CoreLogic::Scene(std::make_shared<Camera2D>())
{
    background_ = CoreLogic::DataProcessing::SpriteStorage::getSprite(CoreLogic::DataProcessing::SpriteStorage::LORE_ITEM);
    cracks_ = CoreLogic::DataProcessing::SpriteStorage::getSprite(CoreLogic::DataProcessing::SpriteStorage::LORE_CRACKS);
}

void Scenes::NoteScene::update()
{

    CoreLogic::EventManagement::SoundHandler &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
    soundHandler.update();

    auto &inputHandler = CoreLogic::EventManagement::InputHandler::getInstance();
    std::vector<CoreLogic::EventManagement::EventEnum> events = inputHandler.handleInput();

    for (CoreLogic::EventManagement::EventEnum event: events)
    {
        if (event == CoreLogic::EventManagement::ENTER)
        {
            CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::IN_GAME);
        }
    }
}

void Scenes::NoteScene::onSwitch()
{
    text_ = CoreLogic::DataProcessing::ActorStorage::getActiveNote()->getText();
    update();
}

void Scenes::NoteScene::draw(RenderTexture2D &pa_canvas)
{
    ClearBackground(BLACK);
    BeginTextureMode(pa_canvas);
    {
        ClearBackground(BLACK);
        DrawTexturePro(background_.getTexture(), background_.getFrame(), {0, 0, 640, 360}, {0, 0}, 0, WHITE);
        DrawTextPro(CoreLogic::DataProcessing::Fonts::getFont(0), text_.c_str(),
                {60, 60}, {0, 0}, 0,
                20, 0, WHITE);
        DrawTextPro(CoreLogic::DataProcessing::Fonts::getFont(0), "Press ENTER to continue",
                {640 - 250, 360 - 40}, {0, 0}, 0,
                20, 0, WHITE);
        DrawTexturePro(cracks_.getTexture(), cracks_.getFrame(), {0, 0, 640, 360}, {0, 0}, 0, {255, 255, 255, 100});
    }
    EndTextureMode();
}
