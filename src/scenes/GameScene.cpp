//
// Created by keanu on 5/23/2024.
//

#include "GameScene.h"
#include "event_management/EventHandler.h"
#include "event_management/SoundHandler.h"
#include "user_interface/HUD.h"
#include "event_management/actors/Enemy.h"
#include "event_management/actors/drones/Worker.h"
#include "event_management/actors/drones/Scout.h"

//assets/data/hive_PROG_tech-demo-map_2024-07-14.tmj
Scenes::GameScene::GameScene(): Scene(std::make_shared<Camera2D>()),
                                po_levels_(std::make_unique<std::vector<CoreLogic::DataProcessing::Level>>(std::initializer_list<CoreLogic::DataProcessing::Level>{
                                        CoreLogic::DataProcessing::Level(std::make_unique<std::vector<std::string>>(std::initializer_list<std::string>{"assets/data/level0.tmj", "lol"}), 0, CoreLogic::DataProcessing::LevelState::Default),
                                        CoreLogic::DataProcessing::Level(std::make_unique<std::vector<std::string>>(std::initializer_list<std::string>{"lel", "assets/data/level0.tmj"}), 1, CoreLogic::DataProcessing::LevelState::War)
                        }))
{
    camera_ -> zoom = 1.0f;
    po_currentMap_ = std::make_unique<CoreLogic::DataProcessing::Map>(po_levels_ -> at(0).getMapPath());
//    CoreLogic::DataProcessing::ActorStorage::setLayers(po_currentMap_ -> getLayers());
    po_previousMap_ = std::make_unique<CoreLogic::DataProcessing::Map>(*po_currentMap_);
    currentLevelID_ = po_levels_ -> at(0).getLevelID();
    previousLevelID_ = currentLevelID_;

    CoreLogic::EventManagement::Actors::Scout drone = { {72, 720}, {72, 720, 32, 32}, 0, {38, 38}, 0};
    CoreLogic::DataProcessing::ActorStorage::setPlayer(std::make_shared<CoreLogic::EventManagement::Actors::Scout>
            (drone));
    auto &eventHandler = CoreLogic::EventManagement::EventHandler::getInstance();
    eventHandler.resetPlayer();

}

int Scenes::GameScene::getCurrentLevelID()
{
    return currentLevelID_;
}

void Scenes::GameScene::draw(RenderTexture2D &pa_canvas)
{
    CoreLogic::UserInterface::Renderer& renderer = *CoreLogic::UserInterface::Renderer::getInstance();
    Color bgColor = po_currentMap_ -> getBgColor();
    renderer.render(CoreLogic::DataProcessing::ActorStorage::getLayers(), po_actors_, *camera_, pa_canvas, bgColor);
}

void Scenes::GameScene::update()
{
    CoreLogic::DataProcessing::global_ticks++;

    Camera2D &camera = *camera_;
    /**
     *@note: eventhandler with movement Event version
     **/

    CoreLogic::EventManagement::EventHandler &eventHandler = CoreLogic::EventManagement::EventHandler::getInstance();
    CoreLogic::EventManagement::SoundHandler &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
    std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> player = CoreLogic::DataProcessing::ActorStorage::getPlayer();
    std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actors::Enemy>>> &enemies = *CoreLogic::DataProcessing::ActorStorage::getEnemies();

    player->update();
    for (auto &pair: enemies)
    {
        for (auto &enemy: pair.second)
        {
            if (enemy == nullptr)
            {
                continue;
            }
            enemy->update();
        }
    }

    /**
     *@todo: InputHandler to be called static
     **/
    eventHandler.handleEvents(po_inputHandler_->handleInput(), player->getId());
    eventHandler.update();

    soundHandler.update();

    CoreLogic::UserInterface::HUD& hud = *CoreLogic::UserInterface::HUD::getInstance();
    hud.update();


    /**
    * @attention: debug stuff
    */

    if (IsKeyPressed(KEY_M))
    {
        if (player->getElevation() == 0)
        {
            player->setElevation(2);
            player->setPosition({985, 55});
        } else if (player->getElevation() == 2) {
            player->setElevation(0);
            player->setPosition({816,648});
        }
    }

    if (IsKeyPressed(KEY_T))
    {
        if(currentLevelID_ == 0)
        {
            currentLevelID_ = 1;

        } else if (currentLevelID_ == 1)
        {
            currentLevelID_ = 0;

        }
        po_currentMap_ = std::make_unique<CoreLogic::DataProcessing::Map>(po_levels_ -> at(currentLevelID_).getMapPath());
        CoreLogic::DataProcessing::ActorStorage::setLayers(po_currentMap_ -> getLayers());
        player = CoreLogic::DataProcessing::ActorStorage::getPlayer();
        if (currentLevelID_ == 1)
        {
            player->setPosition({80,700});
        } else if (currentLevelID_ == 0) {
            player->setPosition({100,100});
        }
        eventHandler.resetPlayer();

    }

    if (IsKeyPressed(KEY_ZERO)) player->setElevation(0);
    if (IsKeyPressed(KEY_ONE)) player->setElevation(1);
    if (IsKeyPressed(KEY_TWO)) player->setElevation(2);

    if (IsKeyPressed(KEY_NINE)) player->setElevation(9);


    Vector2 playerPos = player->getPosition();


    /**
     * @attention: keep hard coded?
     */

    int screenWidth = CoreLogic::DataProcessing::screenWidth_;
    int screenHeight = CoreLogic::DataProcessing::screenHeight_;
    int screenX = screenWidth / 2;
    int screenY = screenHeight / 2;

    Vector2 playerSize = player->getSize();

    if (playerPos.x < screenX - (playerSize.x/2))
    {
        camera.target.x = 0;
    } else if (playerPos.x > 1536 - screenX - (playerSize.x/2)) {
        camera.target.x = 1536 - screenWidth;
    } else {
        camera.target.x = playerPos.x - screenX + (playerSize.x/2);
    }

    if (playerPos.y < screenY - (playerSize.y/2))
    {
        camera.target.y = 0;
    } else if (playerPos.y > 864 - screenY - (playerSize.y/2)) {
        camera.target.y = 864 - screenHeight;
    } else {
        camera.target.y = playerPos.y - screenY + (playerSize.y/2);
    }
}


void Scenes::GameScene::render()
{

}

void Scenes::GameScene::switchLevel()
{

}

void Scenes::GameScene::onSwitch()
{
update();
}
