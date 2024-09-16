//
// Created by Josi on 13.09.2024.
//

#ifndef HIVE_NOTESCENE_H
#define HIVE_NOTESCENE_H

#include "raylib.h"
#include "Scene.h"

namespace Scenes
{
    class NoteScene : public CoreLogic::Scene
    {
    public:
        NoteScene();

        void draw(RenderTexture2D &pa_canvas) override;
        void update() override;
        void onSwitch() override;

    protected:
        CoreLogic::UserInterface::Sprite background_;
        std::string text_;
        CoreLogic::UserInterface::Sprite cracks_;
    };
}

#endif //HIVE_NOTESCENE_H
