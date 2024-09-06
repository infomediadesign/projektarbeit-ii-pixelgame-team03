//
// Created by Josi on 06.09.2024.
//

#ifndef HIVE_DRONESELECTIONSCENE_H
#define HIVE_DRONESELECTIONSCENE_H

#include <memory>
#include <map>
#include "event_management/actors/Drone.h"
#include "Scene.h"

namespace Scenes
{
    class DroneSelectionScene : public CoreLogic::Scene
    {
public:
        DroneSelectionScene();
        void draw(RenderTexture2D &pa_canvas) override;
        void update() override;

        void unlockDrone(CoreLogic::EventManagement::Actors::Drone::DroneType pa_droneType);
    protected:
        static std::shared_ptr<std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool>> po_unlockedDrones_;
        CoreLogic::UserInterface::Sprite sprite_;
    };
}

#endif //HIVE_DRONESELECTIONSCENE_H
