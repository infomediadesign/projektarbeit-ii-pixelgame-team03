//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_SCENE_H
#define RAYLIBSTARTER_SCENE_H

#include <memory>
#include "raylib.h"
#include "event_management/Actor.h"
#include "user_interface/Renderer.h"
#include "event_management/InputHandler.h"

namespace CoreLogic
{
    class Scene
    {
    public:
        Scene() = delete;
        Scene(std::shared_ptr<Camera2D> pa_camera);
        virtual void draw(RenderTexture2D &pa_canvas) = 0;
        virtual void update() = 0;
    protected:
        std::shared_ptr<Camera2D> camera_;
        std::shared_ptr<std::map<int, std::vector<CoreLogic::EventManagement::Actor>>> po_actors_;
        const std::unique_ptr<CoreLogic::EventManagement::InputHandler> inputHandler_;
    };
}


#endif //RAYLIBSTARTER_SCENE_H
