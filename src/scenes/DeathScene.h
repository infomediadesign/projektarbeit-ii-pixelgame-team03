//
// Created by keanu on 5/26/2024.
//

#ifndef RAYLIBSTARTER_DEATHSCENE_H
#define RAYLIBSTARTER_DEATHSCENE_H


#include "Scene.h"

namespace Scenes
{
    class DeathScene : public CoreLogic::Scene
    {
    public:
        DeathScene();

        void draw(RenderTexture2D &pa_canvas) override;
        void update() override;
        void onSwitch() override;

    protected:
        CoreLogic::UserInterface::Sprite sprite_;
        bool restartGame_ = true;

    };
}


#endif //RAYLIBSTARTER_DEATHSCENE_H
