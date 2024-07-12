//
// Created by Josi on 10.07.2024.
//

#include "Sprite.h"

namespace CoreLogic::EventManagement
{

    Sprite::Sprite(std::string pa_path, int pa_frameWidth, int pa_frameHeight,
                   std::vector<std::vector<AnimationState>> pa_animationStates)
    {
        path_ = pa_path;
        frameWidth_ = pa_frameWidth;
        frameHeight_ = pa_frameHeight;
        animationStates_ = pa_animationStates;

        texture_ = LoadTexture(pa_path.c_str());
        frame_ = {0, 0, (float) frameWidth_, (float) frameHeight_};

    }

//    void Sprite::shiftFrame(int pa_stateID, Actor::Direction pa_primaryDirection)
//    {
//        if (pa_stateID == 1 && pa_primaryDirection == primaryDirection_)
//        {
//            currentFrame_++;
//            if (currentFrame_ >= animationStates_[pa_stateID][static_cast<int>(pa_primaryDirection)].steps_)
//            {
//                currentFrame_ = 0;
//            }
//            frame_.x = (float) (currentFrame_ * frameWidth_);
//        }
//        else
//        {
//            frame_.x = 0;
//            frame_.y = animationStates_[pa_stateID][static_cast<int>(pa_primaryDirection)].row_ * frameHeight_;
//            currentFrame_ = 0;
//        }
//    }

    Sprite::Sprite()
    {
        path_ = "";
        frameWidth_ = 0;
        frameHeight_ = 0;
        animationStates_ = std::vector<std::vector<AnimationState>>();
    }
}