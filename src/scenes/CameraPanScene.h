//
// Created by Josi on 19.09.2024.
//

#ifndef HIVE_CAMERAPANSCENE_H
#define HIVE_CAMERAPANSCENE_H


#include "Scene.h"

namespace Scenes
{
    class CameraPanScene : public CoreLogic::Scene
    {
    public:
        CameraPanScene();

        void draw(RenderTexture2D &pa_canvas) override;

        void update() override;

        void onSwitch() override;

    protected:
        Vector2 differenceVector_;
        int panTicks_;
        int restingTicks_;
    };
}

#endif //HIVE_CAMERAPANSCENE_H
