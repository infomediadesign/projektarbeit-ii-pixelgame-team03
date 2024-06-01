//
// Created by keanu on 5/23/2024.
//

#include "GameScene.h"


Scenes::GameScene::GameScene(): Scene(std::make_shared<Camera2D>()),
                                po_levels_(std::make_unique<std::vector<CoreLogic::DataProcessing::Level>>(std::initializer_list<CoreLogic::DataProcessing::Level>{
                                        CoreLogic::DataProcessing::Level(std::make_unique<std::vector<std::string>>(std::initializer_list<std::string>{"assets/data/test.tmj", "lol"}), 0, CoreLogic::DataProcessing::LevelState::Default),
                                        CoreLogic::DataProcessing::Level(std::make_unique<std::vector<std::string>>(std::initializer_list<std::string>{"lel", "lol"}), 1, CoreLogic::DataProcessing::LevelState::War)
                        }))
{
    camera_ -> zoom = 1.0f;
    po_currentMap_ = std::make_unique<CoreLogic::DataProcessing::Map>(po_levels_ -> at(0).getMapPath());
    po_previousMap_ = std::make_unique<CoreLogic::DataProcessing::Map>(*po_currentMap_);
    currentLevelID_ = po_levels_ -> at(0).getLevelID();
    previousLevelID_ = currentLevelID_;
}

int Scenes::GameScene::getCurrentLevelID()
{
    return currentLevelID_;
}

void Scenes::GameScene::draw(RenderTexture2D &pa_canvas)
{
    CoreLogic::UserInterface::Renderer& renderer = *CoreLogic::UserInterface::Renderer::getInstance();
    std::shared_ptr<std::vector<tson::Layer>> layers = po_currentMap_ -> getLayers();
    Color bgColor = po_currentMap_ -> getBgColor();
    renderer.render(layers, po_actors_, *camera_, pa_canvas, bgColor);
}

void Scenes::GameScene::update()
{
    Camera2D &camera = *camera_;
    /**
     * @brief: VORLÄUFIGES Cam-Movement, Wird nachher entfernt
     */
     if (IsKeyPressed(KEY_LEFT))
     {
         camera.target.x -= 24;
     }
     if (IsKeyPressed(KEY_RIGHT))
     {
         camera.target.x += 24;
     }
     if (IsKeyPressed(KEY_UP))
     {
         camera.target.y -= 24;
     }
     if (IsKeyPressed(KEY_DOWN))
     {
         camera.target.y += 24;
     }

}

void Scenes::GameScene::render()
{

}

void Scenes::GameScene::switchLevel()
{

}
