//
// Created by Josi on 08.08.2024.
//

#ifndef HIVE_HUD_H
#define HIVE_HUD_H

#include <memory>
#include <mutex>
#include "raylib.h"
#include "Sprite.h"

namespace CoreLogic::UserInterface{
    class HUD
    {
    public:
        HUD();
        void draw(Rectangle pa_cameraRec);
        void update();
        static HUD* getInstance();
    protected:
        enum HUDElements{
            PORTRAIT,
            MAX,
            CURRENT,

            BUTTONS,
            DISCONNECT,
            MAIN,
            DEATH,
            INTERACT,
        };
        std::vector<Sprite> hudElements_;
        void hudInit();
        static HUD* po_instance_;
        static std::mutex mutex_;
        std::pair<Vector2, std::string> activeTutorialBox_;
    };
}


#endif //HIVE_HUD_H