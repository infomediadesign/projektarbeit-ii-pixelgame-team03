//
// Created by Josi on 06.09.2024.
//

#include "DroneSelectionScene.h"


Scenes::DroneSelectionScene::DroneSelectionScene() :
        Scene(std::make_shared<Camera2D>())
{
    po_unlockedDrones_->insert({CoreLogic::EventManagement::Actors::Drone::WORKER, true});
    po_unlockedDrones_->insert({CoreLogic::EventManagement::Actors::Drone::SCOUT, false});

    sprite_ = CoreLogic::UserInterface::Sprite(std::string pa_path, 640, 360, std::vector<std::vector<AnimationState>>
    pa_animationStates);
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
