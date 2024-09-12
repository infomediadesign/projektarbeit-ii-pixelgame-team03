//
// Created by Josi on 06.09.2024.
//

#include "DroneSelectionScene.h"
#include "event_management/actors/drones/Worker.h"
#include "event_management/actors/drones/Scout.h"
#include "event_management/SoundHandler.h"
#include "event_management/EventHandler.h"


Scenes::DroneSelectionScene::DroneSelectionScene() :
        Scene(std::make_shared<Camera2D>())
{
    auto unlockedDrones = CoreLogic::DataProcessing::ActorStorage::getUnlockedDrones();
    unlockedDrones = std::make_shared<std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool>>();

    unlockedDrones->insert({CoreLogic::EventManagement::Actors::Drone::WORKER, true});
    unlockedDrones->insert({CoreLogic::EventManagement::Actors::Drone::SCOUT, false});

    sprite_ = CoreLogic::DataProcessing::SpriteStorage::getSprite(CoreLogic::DataProcessing::SpriteStorage::DRONE_SELECTION);
}

void Scenes::DroneSelectionScene::draw(RenderTexture2D &pa_canvas)
{
    ClearBackground(BLACK);
    BeginTextureMode(pa_canvas);
    {
        DrawTexturePro(sprite_.getTexture(), sprite_.getFrame(), {0, 0, 640, 360}, {0, 0}, 0, WHITE);
    }
    EndTextureMode();
}

void Scenes::DroneSelectionScene::update()
{
    CoreLogic::EventManagement::SoundHandler &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
    soundHandler.update();

    std::vector<CoreLogic::EventManagement::EventEnum> events = po_inputHandler_->handleInput();

    for (CoreLogic::EventManagement::EventEnum event : events)
    {
        if (event == CoreLogic::EventManagement::INTERACT)
        {
            std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> newDrone;
            CoreLogic::EventManagement::Actors::Drone& player = *CoreLogic::DataProcessing::ActorStorage::getPlayer();

            Vector2 position;
            switch (selectedDroneType_)
            {
            case CoreLogic::EventManagement::Actors::Drone::WORKER:

                position = CoreLogic::DataProcessing::ActorStorage::getActiveSpawnPoint()->getPosition();
                newDrone = std::make_shared<CoreLogic::EventManagement::Actors::Worker>(
                        position,
                        Rectangle{position.x, position.y, 32, 32}, player.getId(), player.getSize(), CoreLogic::DataProcessing::ActorStorage::getActiveSpawnPoint()->getElevation(), player.getMaxHealth(), player.getCurrentHealth());
                break;
            case CoreLogic::EventManagement::Actors::Drone::SCOUT:

                position = CoreLogic::DataProcessing::ActorStorage::getActiveSpawnPoint()->getPosition();
                newDrone = std::make_shared<CoreLogic::EventManagement::Actors::Scout>(
                        position,
                        Rectangle{position.x, position.y, 32, 32}, player.getId(), player.getSize(), CoreLogic::DataProcessing::ActorStorage::getActiveSpawnPoint()->getElevation(),  player.getMaxHealth(), player.getCurrentHealth());
                break;
            }

            CoreLogic::DataProcessing::ActorStorage::setPlayer(newDrone);
            auto &eventHandler = CoreLogic::EventManagement::EventHandler::getInstance();
            eventHandler.resetPlayer();
            CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::IN_GAME);

        } else if (event == CoreLogic::EventManagement::MOVE_RIGHT) {
            if (currentDroneSelection_ == WORKER_SCOUT_UNLOCKED) {
                currentDroneSelection_ = SCOUT_SELECT;
                sprite_.shiftFrame(SCOUT_SELECT);
            }
        } else if (event == CoreLogic::EventManagement::MOVE_LEFT) {
            if (currentDroneSelection_ == SCOUT_SELECT) {
                currentDroneSelection_ = WORKER_SCOUT_UNLOCKED;
                sprite_.shiftFrame(WORKER_SCOUT_UNLOCKED);
            }
        }
    }
}

void Scenes::DroneSelectionScene::onSwitch()
{
    if (CoreLogic::DataProcessing::ActorStorage::isDroneUnlocked(CoreLogic::EventManagement::Actors::Drone::SCOUT)) currentDroneSelection_ =  WORKER_SCOUT_UNLOCKED;
    else currentDroneSelection_ = WORKER_SELECT;
    sprite_.shiftFrame(currentDroneSelection_);

    selectedDroneType_ = CoreLogic::EventManagement::Actors::Drone::WORKER;
    update();
}
