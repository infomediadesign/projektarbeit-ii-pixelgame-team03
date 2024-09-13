//
// Created by Josi on 13.09.2024.
//

#include "NoteScene.h"
#include "event_management/SoundHandler.h"


Scenes::NoteScene::NoteScene()
{

}

void Scenes::NoteScene::update()
{
    text_ = CoreLogic::DataProcessing::ActorStorage::getActiveNote()->getText();

    CoreLogic::EventManagement::SoundHandler &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
    soundHandler.update();

    std::vector<CoreLogic::EventManagement::EventEnum> events = po_inputHandler_->handleInput();

    for (CoreLogic::EventManagement::EventEnum event: events)
    {
        if (event == CoreLogic::EventManagement::INTERACT)
        {

        }
    }
}

void Scenes::NoteScene::onSwitch()
{
    update();
}

void Scenes::NoteScene::draw(RenderTexture2D &pa_canvas)
{
    ClearBackground(BLACK);
    BeginTextureMode(pa_canvas);
    {
        DrawTextPro(CoreLogic::DataProcessing::Fonts::getFont(0), text_.c_str(),
                {20, 20}, {0, 0}, 0,
                20, 0, WHITE);
        DrawTextPro(CoreLogic::DataProcessing::Fonts::getFont(0), "Press ENTER to continue",
                {640 - 100, 360 - 20}, {0, 0}, 0,
                20, 0, WHITE);
    }
    EndTextureMode();
}
