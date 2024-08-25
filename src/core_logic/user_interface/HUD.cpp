//
// Created by Josi on 08.08.2024.
//

#include "HUD.h"
#include "actors/Drone.h"
#include "Store.h"

CoreLogic::UserInterface::HUD::HUD()
{
    hudInit();

}

void CoreLogic::UserInterface::HUD::hudInit() {
    Sprite temp = Sprite(
            "assets/graphics/hive_ARTI_hud-max-life-spritesheet.png", 640, 360,
            {{},
             {},
             {CoreLogic::UserInterface::AnimationState{0, 1}},
             {},
             {CoreLogic::UserInterface::AnimationState{1, 1}},
             {},
             {CoreLogic::UserInterface::AnimationState{2, 1}}}
    );

    hudElements_.push_back(std::make_unique<Sprite>(temp));

    temp = Sprite("assets/graphics/hive_ARTI_hud-current-life-spritesheet.png", 640, 360,
                  {
                          {CoreLogic::UserInterface::AnimationState{0, 1}},
                          {CoreLogic::UserInterface::AnimationState{1, 1}},
                          {CoreLogic::UserInterface::AnimationState{2, 1}},
                          {CoreLogic::UserInterface::AnimationState{3, 1}},
                          {CoreLogic::UserInterface::AnimationState{4, 1}},
                          {CoreLogic::UserInterface::AnimationState{5, 1}},
                          {CoreLogic::UserInterface::AnimationState{6, 1}}
                  }
    );

    hudElements_.push_back(std::make_unique<Sprite>(temp));

    temp = Sprite("assets/graphics/hive_ARTI_hud-portrait.png", 640, 360,
                  {{CoreLogic::UserInterface::AnimationState{0, 1}}});

    hudElements_.push_back(std::make_unique<Sprite>(temp));

    temp = Sprite("assets/graphics/hive_ARTI_hud-example-button-spritesheet.png", 640, 360,
                  {{CoreLogic::UserInterface::AnimationState{0, 1}},
                   {CoreLogic::UserInterface::AnimationState{1, 1}}});

    hudElements_.push_back(std::make_unique<Sprite>(temp));
}

void CoreLogic::UserInterface::HUD::draw(Rectangle pa_cameraRec)
{
    for (auto &element: hudElements_)
    {
        DrawTexturePro(element->getTexture(), element->getFrame(), pa_cameraRec, {0, 0}, 0,
                       WHITE);
    }
}

CoreLogic::UserInterface::HUD* CoreLogic::UserInterface::HUD::po_instance_ = nullptr;
std::mutex CoreLogic::UserInterface::HUD::mutex_;

CoreLogic::UserInterface::HUD *CoreLogic::UserInterface::HUD::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (po_instance_ == nullptr)
    {
        po_instance_ = new HUD();
    }
    return po_instance_;
}

void CoreLogic::UserInterface::HUD::update() {
    CoreLogic::EventManagement::Actors::Drone &player = *CoreLogic::DataProcessing::ActorStorage::getPlayer();

    hudElements_[0]->shiftFrame(player.getMaxHealth() - 1);
    hudElements_[1]->shiftFrame(player.getCurrentHealth() -1);
}
