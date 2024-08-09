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

void CoreLogic::UserInterface::Renderer::render(std::shared_ptr<std::map<int, std::vector<tson::Layer>>> pa_layers, std::shared_ptr<std::map<int,std::vector<EventManagement::Actor>>> &pa_actors, Camera2D &pa_camera, RenderTexture2D &pa_canvas, Color pa_bgColor)
{

    int screenWidth = CoreLogic::DataProcessing::screenWidth_;
    int screenHeight = CoreLogic::DataProcessing::screenHeight_;

    Rectangle cameraRec = {0, 0, 0, 0};
    if (pa_camera.target.x > 0)
    {
        cameraRec.x = floorf(pa_camera.target.x / 24);
    }
    if (pa_camera.target.y > 0)
    {
        cameraRec.y = floorf(pa_camera.target.y / 24);
    }
    if (pa_camera.target.x + screenWidth > 0)
    {
        cameraRec.width = floorf((pa_camera.target.x + screenWidth+24) / 24);
    }
    if (pa_camera.target.y + screenHeight > 0)
    {
        cameraRec.height = floorf((pa_camera.target.y + screenHeight+24) / 24);
    }
    ClearBackground(pa_bgColor);
    BeginTextureMode(pa_canvas);
    {
        ClearBackground(pa_bgColor);
        BeginMode2D(pa_camera);
        {
            ClearBackground(pa_bgColor);
            for (const auto& pair : *pa_layers) {
                const std::vector<tson::Layer> &layers = pair.second;
                for (tson::Layer layer: layers) {
                    if (layer.getType() == tson::LayerType::TileLayer) {
                        if (layer.isVisible())
                        {
                            renderTileLayer(layer, cameraRec);
                        }
                    }
                }
            }

            CoreLogic::EventManagement::Actors::Drone &player = *CoreLogic::DataProcessing::ActorStorage::getPlayer();
            DrawTexturePro(player.getTexture(), player.getFrame(), player.getHitbox(), {0,0}, 0,
             WHITE);

        } EndMode2D();
    } EndTextureMode();
}

void CoreLogic::UserInterface::Renderer::renderTileLayer(tson::Layer &pa_layer, Rectangle pa_cameraRec)
{
    //CoreLogic::DataProcessing::TileMap& tilemap = *CoreLogic::DataProcessing::TileMap::getInstance();
    Texture2D& tileMap = *CoreLogic::DataProcessing::TileMap::getTileMap();
    for (int y = (int)pa_cameraRec.y; y < (int)pa_cameraRec.height; y++)
    {
        for (int x = (int) pa_cameraRec.x; x < (int) pa_cameraRec.width; x++)
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
            tson::Rect tileRect = tile.getDrawingRect();
            Rectangle tileSetRec = {static_cast<float>(tileRect.x), static_cast<float>(tileRect.y), static_cast<float>(tileRect.width), static_cast<float>(tileRect.height)};

            Rectangle destRec = {(float) (x * tileSize), (float) (y * tileSize),
                                 (float) tileSize,
                                 (float) tileSize};

            DrawTexturePro(tileMap, tileSetRec, destRec, {0, 0}, 0, WHITE);
        }
    }
}
