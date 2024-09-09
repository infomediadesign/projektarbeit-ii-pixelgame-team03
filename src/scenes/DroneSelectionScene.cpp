//
// Created by Josi on 06.09.2024.
//

#include "DroneSelectionScene.h"
#include "event_management/actors/drones/Worker.h"
#include "event_management/actors/drones/Scout.h"


Scenes::DroneSelectionScene::DroneSelectionScene() :
        Scene(std::make_shared<Camera2D>())
{
    po_unlockedDrones_ = std::make_shared<std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool>>();

    po_unlockedDrones_->insert({CoreLogic::EventManagement::Actors::Drone::WORKER, true});
    po_unlockedDrones_->insert({CoreLogic::EventManagement::Actors::Drone::SCOUT, false});

    sprite_ = CoreLogic::DataProcessing::SpriteStorage::getSprite(CoreLogic::DataProcessing::SpriteStorage::DRONE_SELECTION);
}

void Scenes::DroneSelectionScene::unlockDrone(CoreLogic::EventManagement::Actors::Drone::DroneType pa_droneType)
{
    if (po_unlockedDrones_->find(pa_droneType) != po_unlockedDrones_->end())
        po_unlockedDrones_->at(pa_droneType) = true;
}

void Scenes::DroneSelectionScene::draw(RenderTexture2D &pa_canvas)
{
    DrawTexturePro(sprite_.getTexture(), sprite_.getFrame(), {0, 0, 640, 360}, {0, 0}, 0, WHITE);
}

void Scenes::DroneSelectionScene::update()
{
    std::vector<CoreLogic::EventManagement::EventEnum> events = po_inputHandler_->handleInput();

    for (CoreLogic::EventManagement::EventEnum event : events)
    {
        if (event == CoreLogic::EventManagement::INTERACT)
        {
            std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> newDrone;
            CoreLogic::EventManagement::Actors::Drone& player = *CoreLogic::DataProcessing::ActorStorage::getPlayer();

            switch (selectedDroneType_)
            {
            case CoreLogic::EventManagement::Actors::Drone::WORKER:
                newDrone = std::make_shared<CoreLogic::EventManagement::Actors::Worker>(
                        CoreLogic::DataProcessing::ActorStorage::getActiveSpawnPoint()->getPosition(),
                        player.getHitbox(), player.getId(), player.getSize(), player.getElevation());
                break;
            case CoreLogic::EventManagement::Actors::Drone::SCOUT:
                newDrone = std::make_shared<CoreLogic::EventManagement::Actors::Scout>(
                        CoreLogic::DataProcessing::ActorStorage::getActiveSpawnPoint()->getPosition(),
                        player.getHitbox(), player.getId(), player.getSize(), player.getElevation());
                break;
            }

            CoreLogic::DataProcessing::ActorStorage::setPlayer(newDrone);
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

bool Scenes::DroneSelectionScene::isDroneUnlocked(CoreLogic::EventManagement::Actors::Drone::DroneType pa_droneType)
{
    return po_unlockedDrones_->at(pa_droneType);
}

void Scenes::DroneSelectionScene::onSwitch()
{
    if (isDroneUnlocked(CoreLogic::EventManagement::Actors::Drone::SCOUT)) currentDroneSelection_ =  WORKER_SCOUT_UNLOCKED;
    else currentDroneSelection_ = WORKER_SELECT;
    sprite_.shiftFrame(WORKER_SELECT);

    selectedDroneType_ = CoreLogic::EventManagement::Actors::Drone::WORKER;
    update();
}
