//
// Created by keanu on 5/26/2024.
//

#ifndef RAYLIBSTARTER_MAINMENUSCENE_H
#define RAYLIBSTARTER_MAINMENUSCENE_H


#include "Scene.h"

namespace Scenes
{
    class MainMenuScene : public CoreLogic::Scene
    {
    public:
        MainMenuScene();

        void draw(RenderTexture2D &pa_canvas) override;
        void update() override;
    };
}


#endif //RAYLIBSTARTER_MAINMENUSCENE_H
