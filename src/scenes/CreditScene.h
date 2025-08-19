//
// Created by Josi on 19.09.2024.
//

#ifndef HIVE_CREDITSCENE_H
#define HIVE_CREDITSCENE_H

#include "Scene.h"

namespace Scenes
{
    class CreditScene : public CoreLogic::Scene
    {
    public:
        CreditScene();

        void draw(RenderTexture2D &pa_canvas) override;
        void update() override;
        void onSwitch() override;

    protected:
        void updateInput();
        bool handleInput_ = false;
        CoreLogic::UserInterface::Sprite background_;
        CoreLogic::UserInterface::Sprite buttons_;
        bool restartGame_ = true;
        int loopdyloops_ = 0;
    };
}

#endif //HIVE_CREDITSCENE_H
