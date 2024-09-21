//
// Created by Josi on 08.08.2024.
//

#ifndef HIVE_HUD_H
#define HIVE_HUD_H

#include <memory>
#include <mutex>
#include "raylib.h"
#include "Sprite.h"
#include "../event_management/actors/objects/TutorialBox.h"

namespace CoreLogic::UserInterface{
    class HUD
    {
    public:
        HUD();
        void draw(Rectangle pa_cameraRec);
        void update();
        static HUD* getInstance();

        bool getLoadingCircleActive();
        void setLoadingCircleActive(bool pa_loadingCircleActive);

    protected:
        void hudInit();

        enum IN_GAME_HUD_Elements{
            PORTRAIT,
            MAX,
            CURRENT,

            BUTTONS,
            TOGGLE,
            MAIN,
            DEATH,
            INTERACT,
        };

        enum CAMERA_PAN_HUD_Elements{
            LOADING,
        };

        std::vector<Sprite> inGameHudElements_;
        std::vector<Sprite> cameraPanHudElements_;
        static HUD* po_instance_;
        static std::mutex mutex_;

        std::shared_ptr<CoreLogic::EventManagement::Object::TutorialBox> activeTutorialBox_;

        bool displayHUD_ = true;

        int loadingCircleFrameRate_;
        bool loadingCircleActive_ = false;
    };
}


#endif //HIVE_HUD_H