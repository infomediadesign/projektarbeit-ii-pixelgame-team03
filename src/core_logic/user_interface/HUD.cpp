

#include "HUD.h"
#include "actors/Drone.h"
#include "data_processing/Store.h"

CoreLogic::UserInterface::HUD::HUD()
{
    hudInit();

}

void CoreLogic::UserInterface::HUD::hudInit()
{
    hudElements_.resize(8);

    hudElements_[PORTRAIT] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_PORTRAIT);
    hudElements_[MAX] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_MAX);
    hudElements_[CURRENT] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_CURRENT);

    hudElements_[BUTTONS] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_BUTTONS);
    hudElements_[DISCONNECT] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_DISCONNECT);
    hudElements_[MAIN] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_MAIN);
    hudElements_[DEATH] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_DEATH);
    hudElements_[INTERACT] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_INTERACT);

    for (Sprite element: hudElements_)
    {
        element.resetFrame(0);
    }
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


    hudElements_[PORTRAIT].shiftFrame(player.getDroneType());
    hudElements_[MAX].shiftFrame(player.getMaxHealth() - 1);
    hudElements_[CURRENT].shiftFrame(player.getCurrentHealth() - 1);


    TraceLog(LOG_INFO, "Ability: %i", player.canAct());
    hudElements_[MAIN].shiftFrame(player.canAct());
    TraceLog(LOG_INFO, "Interact: %i", player.canInteract());
    hudElements_[INTERACT].shiftFrame(player.canInteract());

}