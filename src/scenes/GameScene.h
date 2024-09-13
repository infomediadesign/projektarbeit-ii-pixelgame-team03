//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_GAMESCENE_H
#define RAYLIBSTARTER_GAMESCENE_H


#include "Scene.h"
#include "data_processing/Level.h"
#include "data_processing/Map.h"
#include "event_management/InputHandler.h"

namespace Scenes
{
    class GameScene: public CoreLogic::Scene
    {
    public:
        GameScene();

        void render();
        int getCurrentLevelID();

        void switchLevel(int pa_levelID);

        void draw(RenderTexture2D &pa_canvas) override;
        void update() override;
        void onSwitch() override;

    private:
        int currentLevelID_;
        int previousLevelID_;
        std::unique_ptr<std::vector<CoreLogic::DataProcessing::Level>> po_levels_;
        std::unique_ptr<CoreLogic::DataProcessing::Map> po_loadMap_;
        std::unique_ptr<CoreLogic::DataProcessing::Map> po_previousMap_;
        void updateLevelSwitch();
        void switchMap();
    };
}


#endif //RAYLIBSTARTER_GAMESCENE_H
