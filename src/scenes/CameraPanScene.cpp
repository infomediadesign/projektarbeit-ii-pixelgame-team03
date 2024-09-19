//
// Created by Josi on 19.09.2024.
//

#include "CameraPanScene.h"
#include "event_management/SoundHandler.h"

Scenes::CameraPanScene::CameraPanScene():
        Scene(std::make_shared<Camera2D>())
{

}

void Scenes::CameraPanScene::onSwitch()
{
    panTicks_ = 3 * 60;
    restingTicks_ = 2 * 60;
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
            auto xPos = differenceVector_.x / panTicks_;
            auto yPos = differenceVector_.y / panTicks_;
            camera_->target.x = xPos;
            camera_->target.y = yPos;
        return;
    }
    while (restingTicks_ > 0)
    {
        restingTicks_--;
        return;
    }
    CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::IN_GAME);
}

void Scenes::CameraPanScene::draw(RenderTexture2D &pa_canvas)
{
    CoreLogic::UserInterface::Renderer& renderer = *CoreLogic::UserInterface::Renderer::getInstance();
    renderer.render(CoreLogic::DataProcessing::ActorStorage::getLayers(), po_actors_, *camera_, pa_canvas, BLACK);
}
