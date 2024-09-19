//
// Created by Josi on 19.09.2024.
//

#include "CameraPanScene.h"

Scenes::CameraPanScene::CameraPanScene()
{

}

void Scenes::CameraPanScene::onSwitch()
{
    panTicks_ = 3 * 60;
    restingTicks_ = 2 * 60;
}

void Scenes::CameraPanScene::update()
{
    Vector2 dest = CoreLogic::DataProcessing::ActorStorage::getActiveCameraPan()->getDestination();
    differenceVector_ = {dest.x - camera_->target.x, dest.y - camera_->target.y};

    while (panTicks_ > 0)
    {
        panTicks_--;
        if (panTicks_ == 0)
        {
            camera_->target.x = differenceVector_.x / panTicks_;
            camera_->target.y = differenceVector_.y / panTicks_;
        }
        return;
    }
    while (restingTicks_ > 0)
    {
        restingTicks_--;
        return;
    }
    CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState::IN_GAME);
}