//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_STAGE_H
#define RAYLIBSTARTER_STAGE_H


#include <memory>
#include <vector>
#include <map>
#include "data_processing/Store.h"
#include "raylib.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "PauseScene.h"
#include "SettingsScene.h"

namespace Staging
{
    class Stage
    {
    public:
        Stage(int pa_screenHeight, int pa_screenWidth);
        Stage() = delete;
        ~Stage();

        void draw();
        void update();

    protected:
        std::map<CoreLogic::DataProcessing::GameState, std::shared_ptr<CoreLogic::Scene>> po_scenes_;

        CoreLogic::DataProcessing::GameState currentState_;
        CoreLogic::DataProcessing::GameState previousState_;

        std::shared_ptr<CoreLogic::Scene> po_currentScene_;

        std::shared_ptr<RenderTexture2D> po_canvas_;

        Rectangle renderRec_;
        int renderScale_;
        void letterboxCanvas();



    };
}


#endif //RAYLIBSTARTER_STAGE_H
