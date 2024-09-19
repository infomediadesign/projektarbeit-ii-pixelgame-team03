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

    protected:
        void hudInit();

        enum HUDElements{
            PORTRAIT,
            MAX,
            CURRENT,

            BUTTONS,
            TOGGLE,
            MAIN,
            DEATH,
            INTERACT,
        };

        std::vector<Sprite> hudElements_;
        static HUD* po_instance_;
        static std::mutex mutex_;

        std::shared_ptr<CoreLogic::EventManagement::Object::TutorialBox> activeTutorialBox_;

        bool displayHUD_ = true;
    };
}


#endif //HIVE_HUD_H