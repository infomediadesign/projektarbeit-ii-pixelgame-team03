

#include "HUD.h"
#include "actors/Drone.h"
#include "data_processing/Store.h"

CoreLogic::UserInterface::HUD::HUD()
{
    hudInit();

}

void CoreLogic::UserInterface::HUD::hudInit()
{

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

void CoreLogic::UserInterface::HUD::update()
{
    CoreLogic::EventManagement::Actors::Drone &player = *CoreLogic::DataProcessing::ActorStorage::getPlayer();

    hudElements_[0]->shiftFrame(player.getMaxHealth() - 1);
    hudElements_[1]->shiftFrame(player.getCurrentHealth() - 1);
    hudElements_[2]->shiftFrame(player.getDroneType());
    hudElements_[3]->shiftFrame(player.canInteract());
}