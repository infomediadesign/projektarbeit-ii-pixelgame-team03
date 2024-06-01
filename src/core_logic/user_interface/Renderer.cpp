//
// Created by keanu on 5/22/2024.
//

#include "Renderer.h"

CoreLogic::UserInterface::Renderer* CoreLogic::UserInterface::Renderer::po_instance_ = nullptr;
std::mutex CoreLogic::UserInterface::Renderer::mutex_;

CoreLogic::UserInterface::Renderer *CoreLogic::UserInterface::Renderer::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (po_instance_ == nullptr)
    {
        po_instance_ = new Renderer();
    }
    return po_instance_;
}

void CoreLogic::UserInterface::Renderer::render(std::shared_ptr<std::vector<tson::Layer>> &pa_layers, std::shared_ptr<std::map<int,std::vector<EventManagement::Actor>>> &pa_actors, Camera2D &pa_camera, RenderTexture2D &pa_canvas, Color pa_bgColor)
{
    BeginTextureMode(pa_canvas);
    {
        BeginMode2D(pa_camera);
        {
            ClearBackground(pa_bgColor);
            for (tson::Layer layer: *pa_layers)
            {
                if (layer.getType() == tson::LayerType::TileLayer)
                {
                    renderTileLayer(layer);
                }
            }
        } EndMode2D();
    } EndTextureMode();
}

void CoreLogic::UserInterface::Renderer::renderTileLayer(tson::Layer &pa_layer)
{
    CoreLogic::DataProcessing::TileMap& tilemap = *CoreLogic::DataProcessing::TileMap::getInstance();
    Texture2D& tileMap = *tilemap.getTileMap();
    for (int y = 0; y < pa_layer.getSize().y; y++)
    {
        for (int x = 0; x < pa_layer.getSize().x; x++)
        {
            tson::Tile* tilePtr = pa_layer.getTileData(x, y);
            if (tilePtr == nullptr)
            {
                continue;
            }
            tson::Tile& tile = *tilePtr;
            int tileSize = tile.getTileSize().x;
            int data = static_cast<int>(tile.getId());
            data --;
            if (data < 0)
            {
                continue;
            }
            Rectangle tileSetRec = {(float) (data % (tileMap.width / tileSize) * tileSize),
                                    (float) (data / (tileMap.width / tileSize) * tileSize),
                                    (float) tileSize, (float) tileSize};
            Rectangle destRec = {(float) (x * tileSize), (float) (y * tileSize),
                                 (float) tileSize,
                                 (float) tileSize};

            DrawTexturePro(tileMap, tileSetRec, destRec, {0, 0}, 0, WHITE);
        }
    }
}
