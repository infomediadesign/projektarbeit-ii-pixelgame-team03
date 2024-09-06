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
        void onSwitch() override;

        void unlockDrone(CoreLogic::EventManagement::Actors::Drone::DroneType pa_droneType);
    protected:
        enum DroneSelection{
            WORKER_SELECT,
            WORKER_SCOUT_UNLOCKED,
            SCOUT_SELECT
        };

        CoreLogic::EventManagement::Actors::Drone::DroneType selectedDroneType_;
        static std::shared_ptr<std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool>> po_unlockedDrones_;
        bool isDroneUnlocked(CoreLogic::EventManagement::Actors::Drone::DroneType pa_droneType);
        CoreLogic::UserInterface::Sprite sprite_;
        DroneSelection currentDroneSelection_;
    };
}

#endif //HIVE_DRONESELECTIONSCENE_H
