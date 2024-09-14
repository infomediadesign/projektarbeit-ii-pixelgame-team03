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
                                        CoreLogic::DataProcessing::Level(std::make_unique<std::vector<std::string>>
                                        (std::initializer_list<std::string>{"assets/data/level0.tmj", "lol"}), 0,
                                        CoreLogic::DataProcessing::LevelState::Default, 0),
                                        CoreLogic::DataProcessing::Level(std::make_unique<std::vector<std::string>>(std::initializer_list<std::string>{"lel", "assets/data/level1.tmj"}),
                                                                         1, CoreLogic::DataProcessing::LevelState::War, 1)
                        }))
{
    camera_ -> zoom = 1.0f;
    po_loadMap_ = std::make_unique<CoreLogic::DataProcessing::Map>(po_levels_ -> at(0).getMapPath());
//    CoreLogic::DataProcessing::ActorStorage::setLayers(po_loadMap_ -> getLayers());
    po_previousMap_ = std::make_unique<CoreLogic::DataProcessing::Map>(*po_loadMap_);
    currentLevelID_ = po_levels_ -> at(0).getLevelID();
    previousLevelID_ = currentLevelID_;

    auto spawnPoint = CoreLogic::DataProcessing::ActorStorage::getActiveSpawnPoint();
    CoreLogic::EventManagement::Actors::Worker drone = { {spawnPoint->getPosition().x, spawnPoint->getPosition().y},
            {spawnPoint->getPosition().x, spawnPoint->getPosition().y, 32, 32}, 0,
            {38, 38}, 0};
    CoreLogic::DataProcessing::ActorStorage::setPlayer(std::make_shared<CoreLogic::EventManagement::Actors::Worker>
            (drone));
    auto &eventHandler = CoreLogic::EventManagement::EventHandler::getInstance();
    eventHandler.resetPlayer();

    CoreLogic::DataProcessing::ActorStorage::unlockDrone(CoreLogic::EventManagement::Actors::Drone::DroneType::SCOUT);
}

int Scenes::GameScene::getCurrentLevelID()
{
    return currentLevelID_;
}

void Scenes::GameScene::draw(RenderTexture2D &pa_canvas)
{
    CoreLogic::UserInterface::Renderer& renderer = *CoreLogic::UserInterface::Renderer::getInstance();
    Color bgColor = po_loadMap_ -> getBgColor();
    renderer.render(CoreLogic::DataProcessing::ActorStorage::getLayers(), po_actors_, *camera_, pa_canvas, bgColor);
}

void Scenes::GameScene::update()
{

    Camera2D &camera = *camera_;
    /**
     *@note: eventhandler with movement Event version
     **/

    CoreLogic::EventManagement::EventHandler &eventHandler = CoreLogic::EventManagement::EventHandler::getInstance();
    CoreLogic::EventManagement::SoundHandler &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
    std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> player = CoreLogic::DataProcessing::ActorStorage::getPlayer();
    std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actors::Enemy>>> &enemies = *CoreLogic::DataProcessing::ActorStorage::getEnemies();

    auto levelSwitches = CoreLogic::DataProcessing::ActorStorage::getLevelSwitches()->at(player->getElevation());
    for (auto &levelSwitch: levelSwitches)
    {
        if (CheckCollisionRecs(levelSwitch->getHitbox(), player->getHitbox()))
        {
            player->setElevation(levelSwitch->getSwitchElevation());
            player->setPosition(levelSwitch->getSwitchCoordinates());
            switchLevel(levelSwitch->getNewLevelID());
            return;
        }
    }

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
    

    if (IsKeyPressed(CoreLogic::DataProcessing::DesignConfig::PAUSE_KEYBOARD) || IsGamepadButtonPressed(CoreLogic::DataProcessing::DesignConfig::PAUSE_CONTROLLER, 0))
    {
        CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::MAIN_MENU);
    }

    if (CoreLogic::DataProcessing::global_ticks % 10 == 0)
    {
        auto links = CoreLogic::DataProcessing::ActorStorage::getUplinks();
        for (auto &linklayer: *links)
        {
            for (auto &uplink: linklayer.second)
            {
                uplink->shiftFrame(0);
            }
        }
    }

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

void Scenes::GameScene::switchLevel(int pa_levelID)
{
    int currentLevelID = CoreLogic::DataProcessing::ActorStorage::getCurrentLevelID();
    for (auto &level: *po_levels_)
    {
        if (level.getLevelID() == currentLevelID)
        {
            level.saveLevelStates();
        }
    }

    auto &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
    for (auto &level: *po_levels_)
    {
        if (level.getLevelID() == pa_levelID)
        {
            if (level.getLevelActorStateStorage() == nullptr)
            {
                po_loadMap_ = std::make_unique<CoreLogic::DataProcessing::Map>(level.getMapPath());
            } else {
                level.loadLevelData();
            }
            soundHandler.playAmbient(static_cast<CoreLogic::EventManagement::SoundHandler::SoundEnum>(level.getAmbientId()));
        }
    }
}

void Scenes::GameScene::onSwitch()
{
    if (CoreLogic::DataProcessing::StateMachine::getPreviousState() == CoreLogic::DataProcessing::DRONE_SELECTION)
    {
        auto activeSpawnPoint = CoreLogic::DataProcessing::ActorStorage::getActiveSpawnPoint();
        if (activeSpawnPoint != nullptr)
        {
            if (activeSpawnPoint->getLevel() != CoreLogic::DataProcessing::ActorStorage::getCurrentLevelID())
            {
                switchLevel(activeSpawnPoint->getLevel());
            }
        }
    }
    auto &eventHandler = CoreLogic::EventManagement::EventHandler::getInstance();
    eventHandler.resetPlayer();
    update();
}

