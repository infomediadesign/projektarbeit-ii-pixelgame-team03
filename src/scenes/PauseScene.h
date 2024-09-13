//
// Created by keanu on 5/26/2024.
//

#ifndef RAYLIBSTARTER_PAUSESCENE_H
#define RAYLIBSTARTER_PAUSESCENE_H


#include "Scene.h"

namespace Scenes
{
    class PauseScene : public CoreLogic::Scene
    {
    public:
        PauseScene();

        void draw(RenderTexture2D &pa_canvas) override;
        void update() override;
        void onSwitch() override;
    };
}


#endif //RAYLIBSTARTER_PAUSESCENE_H
