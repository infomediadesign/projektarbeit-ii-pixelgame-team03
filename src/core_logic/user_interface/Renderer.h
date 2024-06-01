//
// Created by keanu on 5/22/2024.
//

#ifndef RAYLIBSTARTER_RENDERER_H
#define RAYLIBSTARTER_RENDERER_H


#include <mutex>
#include <vector>
#include "raylib.h"
#include "data_processing/Store.h"
#include "../../tileson.h"
#include "event_management/Actor.h"


namespace CoreLogic::UserInterface
{
    class Renderer
    {
    private:
        Renderer(){};
        static Renderer* po_instance_;
        static std::mutex mutex_;
        void renderTileLayer(tson::Layer &pa_layer);
    public:
        static Renderer* getInstance();
        void render(std::shared_ptr<std::vector<tson::Layer>> &pa_layers, std::shared_ptr<std::map<int, std::vector<EventManagement::Actor>>> &pa_actors, Camera2D &pa_camera, RenderTexture2D &pa_canvas, Color pa_bgColor);

    };
}



#endif //RAYLIBSTARTER_RENDERER_H
