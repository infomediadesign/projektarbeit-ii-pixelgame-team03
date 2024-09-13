//
// Created by keanu on 5/22/2024.
//

#include "Renderer.h"
#include "HUD.h"

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
    CoreLogic::UserInterface::HUD &hud = *CoreLogic::UserInterface::HUD::getInstance();

    Rectangle cameraRec = {0, 0, 0, 0};
    if (pa_camera.target.x > 0)
    {
        cameraRec.x = floorf(pa_camera.target.x / DataProcessing::global_tileSize);
    }
    if (pa_camera.target.y > 0)
    {
        cameraRec.y = floorf(pa_camera.target.y / DataProcessing::global_tileSize);
    }
    if (pa_camera.target.x + screenWidth > 0)
    {
        cameraRec.width = floorf((pa_camera.target.x + screenWidth + DataProcessing::global_tileSize) / DataProcessing::global_tileSize);
    }
    if (pa_camera.target.y + screenHeight > 0)
    {
        cameraRec.height = floorf((pa_camera.target.y + screenHeight + DataProcessing::global_tileSize) / DataProcessing::global_tileSize);
    }
    ClearBackground(pa_bgColor);
    BeginTextureMode(pa_canvas);
    {
        ClearBackground(pa_bgColor);
        BeginMode2D(pa_camera);
        {
            ClearBackground(pa_bgColor);
            std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> player = CoreLogic::DataProcessing::ActorStorage::getPlayer();
            for (const auto &pair: *pa_layers)
            {
                const std::vector<tson::Layer> &layers = pair.second;
                for (tson::Layer layer: layers)
                {
                    if (layer.getType() == tson::LayerType::TileLayer)
                    {
                        if (layer.isVisible())
                        {
                            renderTileLayer(layer, cameraRec);
                        }
                    }
                }
                auto &visibles = CoreLogic::DataProcessing::ActorStorage::getVisibles()->at(pair.first);
                if (!visibles.empty())
                {
                    for (auto &visible: visibles)
                    {
                        if (visible == nullptr)
                        {
                            continue;
                        }
                        if (!visible->getVisible())
                        {
                            continue;
                        }

                        visible->draw();
                    }
                }
                if (player->getElevation() == pair.first)
                {
                    player->draw();
                }
            }
            /*auto &visibles = *CoreLogic::DataProcessing::ActorStorage::getVisibles();
            for (auto & pair: visibles)
            {
                for (auto &visible: pair.second)
                {
                    if (visible == nullptr)
                    {
                        continue;
                    }
                    if (!visible->getVisible())
                    {
                        continue;
                    }

                    visible->draw();
                }
            }

            player->draw();
*/
            auto &barrels = *CoreLogic::DataProcessing::ActorStorage::getBarrels();
            for (auto & pair: barrels)
            {
                for (auto &barrel: pair.second)
                {
                    if (barrel == nullptr)
                    {
                        continue;
                    }
                    if (!barrel->getVisible())
                    {
                        continue;
                    }
                    barrel->draw();
                }
            }

            hud.draw({pa_camera.target.x, pa_camera.target.y, 640, 360});

        }
        EndMode2D();
    }
    EndTextureMode();
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
