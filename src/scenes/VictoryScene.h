//
// Created by Josi on 13.09.2024.
//

#ifndef HIVE_VICTORYSCENE_H
#define HIVE_VICTORYSCENE_H


#include "Scene.h"

namespace Scenes
{

    class VictoryScene : public CoreLogic::Scene
    {
    public:
        VictoryScene();

        void draw(RenderTexture2D &pa_canvas) override;
        void update() override;
        void onSwitch() override;

    protected:
        void updateInput();
        bool handleInput_ = false;
        CoreLogic::UserInterface::Sprite background_;
        CoreLogic::UserInterface::Sprite buttons_;
        bool restartGame_ = true;
    };

} // Scenes

#endif //HIVE_VICTORYSCENE_H
