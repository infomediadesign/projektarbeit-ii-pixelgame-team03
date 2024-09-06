//
// Created by keanu on 5/26/2024.
//

#ifndef RAYLIBSTARTER_SETTINGSSCENE_H
#define RAYLIBSTARTER_SETTINGSSCENE_H


#include "Scene.h"

namespace Scenes
{
    class SettingsScene : public CoreLogic::Scene
    {
    public:
        SettingsScene();

        void draw(RenderTexture2D &pa_canvas) override;
        void update() override;
        void onSwitch() override;
    };
}


#endif //RAYLIBSTARTER_SETTINGSSCENE_H
