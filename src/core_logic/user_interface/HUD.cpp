

#include "HUD.h"
#include "actors/Drone.h"
#include "data_processing/Store.h"

CoreLogic::UserInterface::HUD::HUD()
{
    hudInit();

}

void CoreLogic::UserInterface::HUD::hudInit()
{

    hudElements_.push_back(DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_BUTTONS));
//    hudElements_.push_back(DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_DISCONNECT));

    hudElements_.push_back(DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_MAX));
    hudElements_.push_back(DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_CURRENT));
    hudElements_.push_back(DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_PORTRAIT));
    hudElements_.push_back(DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_MAIN));
    hudElements_.push_back(DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_INTERACT));
    hudElements_.push_back(DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_DEATH));
}

void CoreLogic::UserInterface::HUD::draw(Rectangle pa_cameraRec)
{
    for (auto &element: hudElements_)
    {
        DrawTexturePro(element.getTexture(), element.getFrame(), pa_cameraRec, {0, 0}, 0,
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

void CoreLogic::UserInterface::HUD::update()
{
    CoreLogic::EventManagement::Actors::Drone &player = *CoreLogic::DataProcessing::ActorStorage::getPlayer();

    hudElements_[2].shiftFrame(player.getMaxHealth() - 1);
    hudElements_[3].shiftFrame(player.getCurrentHealth() - 1);
    hudElements_[4].shiftFrame(player.getDroneType());
    hudElements_[5].shiftFrame(player.canAct());
    hudElements_[6].shiftFrame(player.canInteract());

}