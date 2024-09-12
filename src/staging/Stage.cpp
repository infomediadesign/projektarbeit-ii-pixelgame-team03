//
// Created by keanu on 5/23/2024.
//

#include "Stage.h"
#include "DroneSelectionScene.h"
#include "DeathScene.h"


Staging::Stage::Stage(int pa_screenHeight, int pa_screenWidth)
{
    po_scenes_ =
            {
                {CoreLogic::DataProcessing::GameState::MAIN_MENU, std::make_shared<Scenes::MainMenuScene>()},
                {CoreLogic::DataProcessing::GameState::IN_GAME,   std::make_shared<Scenes::GameScene>()},
                {CoreLogic::DataProcessing::GameState::DRONE_SELECTION, std::make_shared<Scenes::DroneSelectionScene>()},
                {CoreLogic::DataProcessing::GameState::PAUSE,     std::make_shared<Scenes::PauseScene>()},
                {CoreLogic::DataProcessing::GameState::SETTINGS, std::make_shared<Scenes::SettingsScene>()},
                {CoreLogic::DataProcessing::GameState::DEATH, std::make_shared<Scenes::DeathScene>()}
            };

    po_canvas_ = std::make_shared<RenderTexture2D>(LoadRenderTexture(pa_screenWidth, pa_screenHeight));

    CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::MAIN_MENU);
    runningGameState_ = CoreLogic::DataProcessing::StateMachine::getCurrentState();
    po_currentScene_ = po_scenes_[CoreLogic::DataProcessing::StateMachine::getCurrentState()];
}

Staging::Stage::~Stage()
{

}


void Staging::Stage::draw()
{
    BeginDrawing();
    po_currentScene_->draw(*po_canvas_);
    letterboxCanvas();
    EndDrawing();
}

void Staging::Stage::update()
{
     if (CoreLogic::DataProcessing::StateMachine::getCurrentState() == runningGameState_)
     {
         po_currentScene_->update();
     } else {
         po_currentScene_ = po_scenes_[CoreLogic::DataProcessing::StateMachine::getCurrentState()];
         runningGameState_ = CoreLogic::DataProcessing::StateMachine::getCurrentState();
         po_currentScene_->onSwitch();
     }
}


void Staging::Stage::letterboxCanvas()
{
    renderScale_ = std::min(GetScreenHeight() / (float) po_canvas_ -> texture.height, // Calculates how big or small the canvas has to be rendered.
                               GetScreenWidth()  / (float) po_canvas_ -> texture.width); // Priority is given to the smaller side.
    renderScale_ = floorf(renderScale_);
    if (renderScale_ < 1) renderScale_ = 1; // Ensure that scale is at least 1.
    renderRec_ ={};
    renderRec_.width = (float) po_canvas_ -> texture.width * renderScale_;
    renderRec_.height = (float) po_canvas_ -> texture.height * renderScale_;
    renderRec_.x = (GetScreenWidth() - renderRec_.width) / 2.0f;
    renderRec_.y = (GetScreenHeight() - renderRec_.height) / 2.0f;
    DrawTexturePro(po_canvas_ -> texture,
                   Rectangle{0, 0, (float) po_canvas_ -> texture.width, (float) -po_canvas_ -> texture.height},
                   renderRec_,
                   {}, 0, WHITE);
}
