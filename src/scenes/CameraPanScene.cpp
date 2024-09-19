//
// Created by Josi on 19.09.2024.
//

#include "CameraPanScene.h"
#include "event_management/SoundHandler.h"

Scenes::CameraPanScene::CameraPanScene():
        Scene(std::make_shared<Camera2D>())
{
    camera_ -> zoom = 1.0f;
}

void Scenes::CameraPanScene::onSwitch()
{
    auto activeCameraPan = CoreLogic::DataProcessing::ActorStorage::getActiveCameraPan();

    panTicks_ = activeCameraPan->getPanTicks();
    restingTicks_ = activeCameraPan->getRestingTicks();

    camera_->target = activeCameraPan->getPosition();
}

void Scenes::CameraPanScene::update()
{
    CoreLogic::EventManagement::SoundHandler &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
    soundHandler.update();

    Vector2 dest = CoreLogic::DataProcessing::ActorStorage::getActiveCameraPan()->getDestination();
    differenceVector_ = {dest.x - camera_->target.x, dest.y - camera_->target.y};


    while (panTicks_ > 0)
    {
        panTicks_--;
        camera_->target.x += differenceVector_.x / panTicks_;
        camera_->target.y += differenceVector_.y / panTicks_;
        return;
    }
    while (restingTicks_ > 0)
    {
        restingTicks_--;
        camera_->target = dest;
        return;
    }
    CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::IN_GAME);
}

void Scenes::CameraPanScene::draw(RenderTexture2D &pa_canvas)
{
    CoreLogic::UserInterface::Renderer& renderer = *CoreLogic::UserInterface::Renderer::getInstance();
    renderer.render(CoreLogic::DataProcessing::ActorStorage::getLayers(), po_actors_, *camera_, pa_canvas, BLACK);
}
