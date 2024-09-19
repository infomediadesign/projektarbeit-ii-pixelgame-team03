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
    panTicks_ = 3 * 60;
    restingTicks_ = 2 * 60;

    CoreLogic::EventManagement::Actors::Drone& player = *CoreLogic::DataProcessing::ActorStorage::getPlayer();
    Vector2 playerPos = player.getPosition();

    int screenWidth = CoreLogic::DataProcessing::screenWidth_;
    int screenHeight = CoreLogic::DataProcessing::screenHeight_;
    int screenX = screenWidth / 2;
    int screenY = screenHeight / 2;

    Vector2 playerSize = player.getSize();

    if (playerPos.x < screenX - (playerSize.x/2))
    {
        camera_->target.x = 0;
    } else if (playerPos.x > 1536 - screenX - (playerSize.x/2)) {
        camera_->target.x = 1536 - screenWidth;
    } else {
        camera_->target.x = playerPos.x - screenX + (playerSize.x/2);
    }

    if (playerPos.y < screenY - (playerSize.y/2))
    {
        camera_->target.y = 0;
    } else if (playerPos.y > 864 - screenY - (playerSize.y/2)) {
        camera_->target.y = 864 - screenHeight;
    } else {
        camera_->target.y = playerPos.y - screenY + (playerSize.y/2);
    }
}

void Scenes::CameraPanScene::update()
{
    CoreLogic::EventManagement::SoundHandler &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
    soundHandler.update();
    Camera2D &camera = *camera_;


    Vector2 dest = CoreLogic::DataProcessing::ActorStorage::getActiveCameraPan()->getDestination();
    differenceVector_ = {dest.x - camera_->target.x, dest.y - camera_->target.y};


    while (panTicks_ > 0)
    {
        panTicks_--;
            auto xPos = differenceVector_.x / panTicks_;
            auto yPos = differenceVector_.y / panTicks_;
            camera.target.x = xPos;
            camera.target.y = yPos;
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
