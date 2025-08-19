

#include "HUD.h"
#include "actors/Drone.h"
#include "data_processing/Store.h"
#include "InputHandler.h"

CoreLogic::UserInterface::HUD::HUD()
{
    hudInit();

}

void CoreLogic::UserInterface::HUD::hudInit()
{
    inGameHudElements_.resize(8);
    cameraPanHudElements_.resize(1);

    inGameHudElements_[PORTRAIT] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_PORTRAIT);
    inGameHudElements_[MAX] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_MAX_LIFE);
    inGameHudElements_[CURRENT] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_CURRENT_LIFE);

    inGameHudElements_[BUTTONS] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_BUTTONS);
    inGameHudElements_[TOGGLE] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_TOGGLE);
    inGameHudElements_[MAIN] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_MAIN_ABILITY);
    inGameHudElements_[DEATH] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_DEATH_ABILITY);
    inGameHudElements_[INTERACT] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_INTERACT);

    cameraPanHudElements_[LOADING] = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::HUD_LOADING);

    for (Sprite element: inGameHudElements_)
    {
        element.resetFrame(0);
    }

    for (Sprite element: cameraPanHudElements_)
    {
        element.resetFrame(0);
    }

    loadingCircleFrameRate_ = (int) CoreLogic::DataProcessing::DesignConfig::CANCEL_CAMERA_PAN / (cameraPanHudElements_
            [LOADING].getFrameAmount()-1);
    if (loadingCircleFrameRate_ < 1)
    {
        loadingCircleFrameRate_ = 1;
    }
}

void CoreLogic::UserInterface::HUD::draw(Rectangle pa_cameraRec)
{
    if (CoreLogic::DataProcessing::StateMachine::getCurrentState() == CoreLogic::DataProcessing::GameState::CAMERA_PAN)
    {
        for (auto &element: cameraPanHudElements_)
        {
            DrawTexturePro(element.getTexture(), element.getFrame(), pa_cameraRec, {0, 0}, 0, WHITE);
        }
    } else {
        if (displayHUD_)
        {
            for (auto &element: inGameHudElements_)
            {
                DrawTexturePro(element.getTexture(), element.getFrame(), pa_cameraRec, {0, 0}, 0, WHITE);
            }
        }
        DrawTexturePro(inGameHudElements_[TOGGLE].getTexture(), inGameHudElements_[TOGGLE].getFrame(), pa_cameraRec,
                {0, 0}, 0, WHITE);
    }
    if (!(activeTutorialBox_ == nullptr))
    {
        DrawTextPro(CoreLogic::DataProcessing::Fonts::getFont(0), activeTutorialBox_->getText().c_str(),
                {activeTutorialBox_->getAnchor().x, activeTutorialBox_->getAnchor().y}, {0, 0}, 0,
                activeTutorialBox_->getFontSize(), activeTutorialBox_->getSpacing(), WHITE);
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

    inGameHudElements_[PORTRAIT].shiftFrame(player.getDroneType());
    inGameHudElements_[MAX].shiftFrame(player.getMaxHealth() - 1);
    inGameHudElements_[CURRENT].shiftFrame(player.getCurrentHealth() - 1);

    inGameHudElements_[BUTTONS].shiftFrame(!CoreLogic::EventManagement::InputHandler::gatLastInputKeyboard());
    inGameHudElements_[MAIN].shiftFrame(player.canAct());
    inGameHudElements_[DEATH].shiftFrame(player.canDeathAbility());
    inGameHudElements_[INTERACT].shiftFrame(player.canInteract());
    inGameHudElements_[TOGGLE].shiftFrame(!CoreLogic::EventManagement::InputHandler::gatLastInputKeyboard());

    if (loadingCircleActive_ && CoreLogic::DataProcessing::global_ticks % loadingCircleFrameRate_ == 0)
    {
        cameraPanHudElements_[LOADING].shiftFrame(0);
    }

    activeTutorialBox_ = nullptr;
    auto tutorialBoxes = CoreLogic::DataProcessing::ActorStorage::getTutorialBoxes()->at(player.getElevation());
    for (auto tutorialBox: tutorialBoxes)
    {
        if (CheckCollisionRecs(tutorialBox->getHitbox(), player.getHitbox()))
        {
            activeTutorialBox_ = tutorialBox;
            break;
        }
    }

    auto &inputHandler = CoreLogic::EventManagement::InputHandler::getInstance();
    std::vector<CoreLogic::EventManagement::EventEnum> events = inputHandler.handleInput();

    for (CoreLogic::EventManagement::EventEnum event: events)
    {
        if (event == CoreLogic::EventManagement::HUD_TOGGLE)
        {
            displayHUD_ = !displayHUD_;
        }
    }
}

bool CoreLogic::UserInterface::HUD::getLoadingCircleActive()
{
    return loadingCircleActive_;
}

void CoreLogic::UserInterface::HUD::setLoadingCircleActive(bool pa_loadingCircleActive)
{
    loadingCircleActive_ = pa_loadingCircleActive;
    if (!loadingCircleActive_)
    {
        cameraPanHudElements_[LOADING].resetFrame(0);
    }
}

