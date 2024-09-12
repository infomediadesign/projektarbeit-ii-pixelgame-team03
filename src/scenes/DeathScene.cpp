//
// Created by keanu on 5/26/2024.
//

#include "DeathScene.h"
#include "event_management/SoundHandler.h"
#include "../staging/Game.h"

Scenes::DeathScene::DeathScene(): Scene(std::make_shared<Camera2D>())
{
    sprite_ = CoreLogic::DataProcessing::SpriteStorage::getSprite
            (CoreLogic::DataProcessing::SpriteStorage::DEATH_SCENE);
}

void Scenes::DeathScene::draw(RenderTexture2D &pa_canvas)
{
    ClearBackground(BLACK);
    BeginTextureMode(pa_canvas);
    {
        DrawTexturePro(sprite_.getTexture(), sprite_.getFrame(), {0, 0, 640, 360}, {0, 0}, 0, WHITE);
    }
    EndTextureMode();
}

void Scenes::DeathScene::update()
{

    std::vector<CoreLogic::EventManagement::EventEnum> events = po_inputHandler_->handleInput();

    for (CoreLogic::EventManagement::EventEnum event : events)
    {
        if (event == CoreLogic::EventManagement::INTERACT)
        {
            //@todo: reset level
            if (!restartGame_)
            {
                CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::MAIN_MENU);
            } else {
                CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::IN_GAME);
            }

        } else if (event == CoreLogic::EventManagement::MOVE_DOWN) {
            if (restartGame_) {
                restartGame_ = false;
                sprite_.shiftFrame(1);
            }
        } else if (event == CoreLogic::EventManagement::MOVE_UP) {
            if (!restartGame_) {
                restartGame_ = true;
                sprite_.shiftFrame(0);
            }
        }
    }
}

void Scenes::DeathScene::onSwitch()
{
    update();
}
